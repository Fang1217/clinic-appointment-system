#ifndef QUEUE_L_HPP
#define QUEUE_L_HPP

typedef int QueueItemType;

class Queue
{
public:
    Queue();
    ~Queue();
    int count;
    bool isEmpty();
    void enqueue(QueueItemType newItem);
    void dequeue();
    QueueItemType getFront();
    QueueItemType getFrontAndPop();

private:
    struct QueueNode
    {
        QueueItemType item;
        QueueNode* next;
    }; // end QueueNode

    QueueNode* backPtr;
    QueueNode* frontPtr;

}; // end Queue

#endif