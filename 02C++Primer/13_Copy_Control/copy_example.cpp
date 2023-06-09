#include <iostream>
#include "copy_example.h"
using namespace std;

void Message::save(Folder &f){
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f){
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_Folders(const Message &msg){
    for(auto f : msg.folders)
        f->addMsg(this);
}

Message::Message(const Message &msg):contents(msg.contents),folders(msg.folders){
    add_to_Folders(msg);
}

void Message::remove_from_Folders(){
    for(auto f : folders)
        f->remMsg(this);
}

Message& Message::operator=(const Message &rhs){
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

Message::~Message(){
    remove_from_Folders();
}

void swap(Message &lhs, Message &rhs){
    using std::swap;

    lhs.remove_from_Folders();
    rhs.remove_from_Folders();

    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    lhs.add_to_Folders(lhs);
    rhs.add_to_Folders(rhs);
}

Folder::Folder(const Folder &f):msgs(f.msgs){
    add_to_Message(f);
}

Folder& Folder::operator=(const Folder &rhs){
    remove_from_Message();
    msgs = rhs.msgs;
    add_to_Message(rhs);
    return *this;
}

void Folder::add_to_Message(const Folder &f){
    for(auto m : f.msgs)
        m->addFldr(this);
}

void Folder::remove_from_Message(){
    for(auto m : msgs)
        m->remFldr(this);
}

void Folder::print_debug(){
    for(auto m : msgs)
        cout << m->contents << " ";
    cout << endl;
}

void swap(Folder &lhs, Folder &rhs){
    using std::swap;
    lhs.remove_from_Message();
    rhs.remove_from_Message();

    swap(lhs.msgs, rhs.msgs);

    lhs.add_to_Message(lhs);
    rhs.add_to_Message(rhs);
}

int main(){

    return 0;
}