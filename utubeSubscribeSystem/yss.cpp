/*
don't you think Channel class shouldn’t need to know internal details of User, and vice versa., How to avoid this
 in my current architecture what's the thing which I need to learn to avoid this 

Ideally, Channel and User should not need to know each other's internal details. This reduces coupling and makes your code more modular, maintainable, and testable.
What’s Happening Now?
Channel directly accesses User* and vice versa.
They call each other’s methods and sometimes manipulate each other’s data structures.
How to Avoid This?
1. Use Interfaces/Abstract Classes
Define interfaces (pure virtual classes in C++) for the behaviors you need (e.g., ISubscriber, INotifiable).
Channel interacts with the interface, not the concrete User class.
User implements the interface.

class ISubscriber {
public:
    virtual void notify(const std::string& message) = 0;
    virtual ~ISubscriber() = default;
};

class User : public ISubscriber {
    // ...
    void notify(const std::string& message) override {
        // handle notification
    }
};
Now, Channel only knows about ISubscriber*, not User*.
2. Event/Observer Pattern
Use the Observer pattern, where Channel only knows about a list of observers (subscribers) via an interface.
User subscribes/unsubscribes via the interface, and Channel notifies via the interface.
3. Dependency Injection
Pass dependencies (like notification handlers) into constructors or methods, rather than creating them inside the class.
This way, classes depend on abstractions, not concrete implementations.
4. Law of Demeter (Principle of Least Knowledge)
Each unit should only talk to its immediate friends, not friends of friends.
Avoid code like user->getChannel()->getSubscribers().
What Should You Learn?
Interfaces and Abstract Classes in C++
Observer Pattern (and how to implement it with interfaces)
Dependency Injection (manual in C++, or using frameworks in other languages)
Law of Demeter

here I have a doubt you are defining notify method under User class but, currently we are notifing our subscriber
 through  Channel class sendNotificationToAllSubscriber(), so shouldn't we define that on Channel class instead,
  pls correct me if I am missing something

This is a great question and a very common point of confusion when learning the Observer pattern!
Key Concept: Who Notifies Whom?
Channel is the "subject" (the thing being observed).
User is the "observer" (the thing that wants to be notified).
The notify method belongs to the observer (User), not the subject (Channel).
How It Works:
The Channel keeps a list of ISubscriber* (observers).
When something happens (e.g., a new video is posted), the Channel calls notify(...) on each observer in its list.
The User implements the notify method to handle the notification (e.g., print a message, update a feed, etc.).
Why Not Put notify in Channel?
The Channel is responsible for sending notifications, but it does so by calling notify on its subscribers.
The User (as a subscriber) decides what to do when notified (e.g., display a message, update UI, etc.).
This separation allows you to have many different types of subscribers, each handling notifications differently.

*/











#include<iostream>
#include<set>
#include<map>
#include <string>
#include <optional>

using namespace std;

class Channel;
class Video;
class ChannelFactory;

// this will act as an interface as cpp does have interfaces pure abstract class acts
// like them
class ISubscriber {
public:
    virtual void notify(const string& message) = 0;
    virtual void subscribeToAChannel() = 0;
    virtual void userUnsubscribeToAChannel() = 0;
    virtual string getName() const = 0;
    // virtual ~ISubscriber() = default;
};

class IChannel { // or we can also name it ISubject
public:
    // virtual string getName() = 0;
    virtual void sendNotificationToAllSubscriber() = 0;
    virtual void addUserToSubscribedList(ISubscriber* user) = 0;
    virtual void removeUserFromSubscribedList(ISubscriber* user) = 0;
    // ... other channel-related methods
    // virtual ~IChannel() = default;
};

class User : public ISubscriber {
    string name;
    // string userId;
    int subscribedChannels;
    int subscribers;
    int totalLikedVideos;
    set<IChannel*>listOfSubscribedChannels;
    map<string, vector<Video*> >currentVideosInTheFeed;
    set<IChannel*>channelCreatedByUser;
    set<Video*>videoPostedByUser;

    public:
    
    User(string name) {
        this->name = name;
        this->subscribedChannels = 0;
        this->subscribers = 0;
        this->totalLikedVideos = 0;
        this->listOfSubscribedChannels = set<IChannel*>();
        this->currentVideosInTheFeed = map<string, vector<Video*> >();
    }

    void subscribeToAChannel(IChannel* channel);

    void userUnsubscribeToAChannel(IChannel* channel);

    void getAllVideosOfAChannel(IChannel* channel, string name) {
     vector<Video*> videos;
     if(listOfSubscribedChannels.find(channel) != listOfSubscribedChannels.end()) {
         cout<<this->name<<" has subscribed to "<<name<<endl;
         videos = this->currentVideosInTheFeed[name];
     }else{
         cout<<this->name<<" has not subscribed to "<<name<<endl;
         return ;
     }
     cout<<"Videos of "<<name << " are "<<endl;
     for(auto video: videos) {
         cout<<"video "<<video<<endl;
     }
    }

    void notify(const string &message) override {
        cout<<"User " << this->name << " has been notified";
    }

    string getName() const override {
        return this->name;
    }

    IChannel* createChannel(string name);

    // IChannel* createChannel(string name) {
    // IChannel* channel = ChannelFactory::createChannel(name, this);
    // this->channelCreatedByUser.insert(channel);
    // return channel;
    // }   

    Video* postVideo(string name);

    // void createChannel(string name) {
    //     IChannel* channel = new IChannel(name, this->name); 
    //     this->channelCreatedByUser.insert((channel));
    //     return channel;
    // }

    // void postVideo() {
    //     Video* video = new Video()
    //     this->videoPostedByUser.insert(video);
    // }
};

class Video {
    string name;
    User* user;
    Channel* uploadedBy;

    public:

    Video(string name, User* user) {
        this->name = name;
        this->user = user;
        // this->uploadedBy = channel;
    }

    User* getUser() {
        return this->user;
    }

    string getName() {
        return this->name;
    }
};

class Channel : public IChannel {
    string name; // same as user name
    // set<User*>listOfSubscribers;
    set<ISubscriber*>subscribers;
    vector<Video*>listOfVideos;
    ISubscriber* user;

    public:

    Channel(string name, ISubscriber* user) {
        this->name = name;
        this->user = user;
        this->subscribers = set<ISubscriber*>();
    }

    set<ISubscriber*>getSubscribers() {
        return this->subscribers;
    }

    void addUserToSubscribedList(ISubscriber* user) {
        subscribers.insert(user);
    }

    void printCurrentSubscribers() {
        cout<<"subscribers of this channel "<< " are "<<endl;
        for(auto subscriber: subscribers) {
            cout<< subscriber->getName()<<endl;
        }
    }

    void removeUserFromSubscribedList(ISubscriber* user) {
        subscribers.erase(user);
    }

    void sendNotificationToAllSubscriber() {
        for(auto subscriber: subscribers) {
            subscriber->notify("hello");
            // cout<<"hey "<<subscriber<<" new video is out pls watch it and subscribe"<<endl;
        }
    }

    vector<Video*>getVideos() {
        return this->listOfVideos;
    }

    string channelName() {
        return this->name;
    }

};

class ChannelFactory {
public:
    static IChannel* createChannel(const std::string& name, ISubscriber* owner) {
        return new Channel(name, owner); // returns as IChannel*
    }
};

// IChannel* User::createChannel(string name) {
//     Channel* channel = new Channel(name, this); 
//     this->channelCreatedByUser.insert((channel));
//     return channel;
// }

IChannel* User::createChannel(string name) {
    IChannel* channel = ChannelFactory::createChannel(name, this);
    this->channelCreatedByUser.insert(channel);
    return channel;
}

Video* User::postVideo(string name) {
    Video* video = new Video(name, this);
    this->videoPostedByUser.insert(video);
    // after this the subscriber should be notified. here we should be having a 
    // or a pointer to Channel's listOfSubscribers, because user himself don't know
    // what are his subscriber
    set<IChannel*> channelList = this->channelCreatedByUser;
    // for now let's assume the user only create a single channel
    IChannel* firstChannel = *channelList.begin();
    // for we have the reference to his first channel 
    // just send the notifcation to all the subscriber of this channel
    firstChannel->sendNotificationToAllSubscriber();
    return video;
}

void User::subscribeToAChannel(IChannel* channel) {
    this->subscribedChannels++;
    listOfSubscribedChannels.insert(channel);
    // now the channel's internal list should know who has subscribed it
    channel->addUserToSubscribedList(this);
    cout<<"hey "<<this->name<<" you are subscirbed to "<<channel->channelName()<<endl;
}

void User::userUnsubscribeToAChannel(IChannel* channel) {
    this->subscribedChannels--;
    listOfSubscribedChannels.erase(channel);
    // now the channel's internal list should know who has subscribed it
    channel->removeUserFromSubscribedList(this);
    cout<<"hey "<<this->name<<" you are unsubscirbed from "<<channel->channelName()<<endl;
}

int main() {
    User* user1 = new User("John");
    User* user2 = new User("Jane");
    IChannel * channel1 = user1->createChannel("abhinav's vlog");
    channel1->printCurrentSubscribers();
    user2->subscribeToAChannel(channel1);
    channel1->printCurrentSubscribers();
    user1->postVideo("diwali vlog");
    user2->userUnsubscribeToAChannel(channel1);
    delete channel1;
    delete user1;
    delete user2;
    // Channel* channel1 = new Channel("vlogging", user1);
    // Video* video1 = new Video("diwali vlog", user1,channel1);
    // user2->getAllVideosOfAChannel(channel1, "vlogging");
    // user2->subscribeToAChannel(channel1);
    // user2->getAllVideosOfAChannel(channel1, "vlogging");
    // user2->userUnsubscribeToAChannel(channel1);
    // user2->getAllVideosOfAChannel(channel1, "vlogging");
}