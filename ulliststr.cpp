#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
//add an element to the back of the list
void ULListStr::push_back(const std::string& val) {
  //if list is empty
  if(tail_ == nullptr) {
    tail_ = new Item;
    head_ = tail_;

    tail_->val[tail_->last++] = val;
    size_++;
    return;
  }
  //if last node in array is full, make new node
  else if(tail_->last == 10) {
    Item* newNode = new Item;
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
  }
  //add value to current tail nod
  // tail_->val[tail_->last] = val;
  tail_->val[tail_->last++] = val;
  size_++;
}

//add element to front of the list
void ULListStr::push_front(const std::string& val) {
  //if list is empty
  if(head_ == nullptr) {
    head_ = new Item;
    tail_ = head_;

    head_->first = 9;
    head_->last = 10;
    head_->val[9] = val;
    size_++;
    //head_->val[head_->last++] = val;
    return;
  }
  //if first index is at start, create new node
  if(head_->first == 0) {
    Item* newNode = new Item;
    newNode->val[9] = val;
    newNode->first = 9;
    newNode->last = 10;
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
  }
  else {
    head_->first--;
    head_->val[head_->first]= val;
  }
  size_++;
}

//removes front element from list
void ULListStr::pop_front() {
  if(!head_ || size_ == 0) {
    return;
  }

  head_->first++;
  size_--;
  //remove current node if empty
  if(head_->first == 10) {
    Item* del = head_;
    head_ = head_->next;
    if(head_) {
      head_->prev = nullptr;
    }
    else {
      tail_ = nullptr;
    }
    delete del;
  }
 
}

//remove last element from list
void ULListStr::pop_back() {
  if(tail_ == nullptr || size_ == 0) {
    return;
  }
  tail_->last--;
  size_--;

  //remove current node if empty
  if(tail_->first == tail_->last) {
    Item* del = tail_;
    tail_ = tail_->prev;
    if(tail_) {
      tail_->next = nullptr;
    }
    else {
      head_ = nullptr;
    }
    delete del;
    // size_--;
  }
 
}

//returns reference to last element
const std::string &ULListStr::back() const{
  
  return tail_->val[tail_->last - 1];
}

//reterns reference to fist element
const std::string &ULListStr::front() const{

  return head_->val[head_->first];
}

//get value at location
std::string* ULListStr::getValAtLoc(size_t loc) const{

  //check for out of bounds
  if(size_==0 || loc >= 10 * size_) {
    return nullptr;
  }

  Item* temp = head_;
  
  int steps = loc;
  int firstIndex = temp->first;

  //look for correct node
  while(steps > (9 - firstIndex) && temp->next) {
    temp = temp->next;
    steps -= 10;
  }

  int answer = firstIndex + steps;
  //check for valid range
  if(answer >= temp->last){
    return nullptr;
  }

  return &temp->val[answer];

  return nullptr;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
