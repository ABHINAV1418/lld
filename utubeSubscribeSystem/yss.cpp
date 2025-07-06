#include<iostream>
#include<set>
#include<map>
#include <string>
#include <optional>

using namespace std;

class Channel;
class Video;

class User {
    string name;
    // string userId;
    int subscribedChannels;
    int subscribers;
    int totalLikedVideos;
    set<Channel*>listOfSubscribedChannels;
    map<string, vector<Video*> >currentVideosInTheFeed;
    set<Channel*>channelCreatedByUser;
    set<Video*>videoPostedByUser;

    public:
    
    User(string name) {
        this->name = name;
        this->subscribedChannels = 0;
        this->subscribers = 0;
        this->totalLikedVideos = 0;
        this->listOfSubscribedChannels = set<Channel*>();
        this->currentVideosInTheFeed = map<string, vector<Video*> >();
    }

    void subscribeToAChannel(Channel* channel);

    void userUnsubscribeToAChannel(Channel* channel);

    void getAllVideosOfAChannel(Channel* channel, string name) {
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

    Channel* createChannel(string name);
    Video* postVideo(string name);

    // void createChannel(string name) {
    //     Channel* channel = new Channel(name, this->name); 
    //     this->channelCreatedByUser.insert((channel));
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

class Channel {
    string name; // same as user name
    set<User*>listOfSubscribers;
    vector<Video*>listOfVideos;
    User* user;

    public:

    Channel(string name, User* user) {
        this->name = name;
        this->user = user;
        this->listOfSubscribers = set<User*>();
    }

    set<User*>getSubscribers() {
        return this->listOfSubscribers;
    }

    void addUserToSubscribedList(User* user) {
        listOfSubscribers.insert(user);
    }

    void printCurrentSubscribers() {
        cout<<"subscribers of this channel "<<this->name <<" are "<<endl;
        for(auto subscriber: listOfSubscribers) {
            cout<< subscriber<<endl;
        }
    }

    void removeUserFromSubscribedList(User* user) {
        listOfSubscribers.erase(user);
    }

    void sendNotificationToAllSubscriber() {
        for(auto subscriber: listOfSubscribers) {
            cout<<"hey "<<subscriber<<" new video is out pls watch it and subscribe"<<endl;
        }
    }

    vector<Video*>getVideos() {
        return this->listOfVideos;
    }

    string channelName() {
        return this->name;
    }

};

Channel* User::createChannel(string name) {
    Channel* channel = new Channel(name, this); 
    this->channelCreatedByUser.insert((channel));
    return channel;
}

Video* User::postVideo(string name) {
    Video* video = new Video(name, this);
    this->videoPostedByUser.insert(video);
    // after this the subscriber should be notified. here we should be having a 
    // or a pointer to Channel's listOfSubscribers, because user himself don't know
    // what are his subscriber
    set<Channel*> channelList = this->channelCreatedByUser;
    // for now let's assume the user only create a single channel
    Channel* firstChannel = *channelList.begin();
    // for we have the reference to his first channel 
    // just send the notifcation to all the subscriber of this channel
    firstChannel->sendNotificationToAllSubscriber();
    return video;
}

void User::subscribeToAChannel(Channel* channel) {
    this->subscribedChannels++;
    listOfSubscribedChannels.insert(channel);
    // now the channel's internal list should know who has subscribed it
    channel->addUserToSubscribedList(this);
    cout<<"hey "<<this->name<<" you are subscirbed to "<<channel->channelName()<<endl;
}

void User::userUnsubscribeToAChannel(Channel* channel) {
    this->subscribedChannels--;
    listOfSubscribedChannels.erase(channel);
    // now the channel's internal list should know who has subscribed it
    channel->removeUserFromSubscribedList(this);
    cout<<"hey "<<this->name<<" you are unsubscirbed from "<<channel->channelName()<<endl;
}

int main() {
    User* user1 = new User("John");
    User* user2 = new User("Jane");
    Channel * channel1 = user1->createChannel("abhinav's vlog");
    channel1->printCurrentSubscribers();
    user2->subscribeToAChannel(channel1);
    // user1->postVideo("diwali vlog");
    user2->userUnsubscribeToAChannel(channel1);
    // Channel* channel1 = new Channel("vlogging", user1);
    // Video* video1 = new Video("diwali vlog", user1,channel1);
    // user2->getAllVideosOfAChannel(channel1, "vlogging");
    // user2->subscribeToAChannel(channel1);
    // user2->getAllVideosOfAChannel(channel1, "vlogging");
    // user2->userUnsubscribeToAChannel(channel1);
    // user2->getAllVideosOfAChannel(channel1, "vlogging");
}