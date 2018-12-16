#include <string.h>
#include "CircleBuffer.h"
namespace sqh{
CircleBuffer::CircleBuffer(int capacity)
: m_capacity(capacity),m_size(0),m_buffer(nullptr),m_start(0),m_end(0){}

bool CircleBuffer::construct(){
    bool ret = false;
    m_buffer = new char[m_capacity]();
    if(m_buffer){
        ret = true;
    }

    return ret;

}

CircleBuffer*  CircleBuffer::NewInstance(size_t capacity){
    CircleBuffer* ret = new CircleBuffer(capacity);
    if(!ret || !ret->construct()){
        delete ret;
        ret = nullptr;
    }

    return ret;

}

bool CircleBuffer::set(char* data , const size_t len){
    bool ret = false;
    if(data == nullptr || len == 0){
        return ret;   
    }
    int unUsed = m_capacity - m_size;

    if(len <= unUsed){
        if(m_capacity - m_end >= len){
            memcpy(m_buffer + m_end,data,len);
            m_end = m_end + len;
        }else{
            memcpy(m_buffer + m_end,data,m_capacity - m_end);
            memcpy(m_buffer,data + (m_capacity - m_end),len - (m_capacity - m_end));
            m_end = len - (m_capacity - m_end);
        }

        m_size += len;
        ret = true;
    }

    return ret;
}
bool CircleBuffer::get(char* buffer, const size_t len){
    bool ret = false;

    if(buffer == nullptr || len == 0){
        return  ret;
    }

    if(m_size >= len){
        if(m_capacity - m_start >= len){
            memcpy(buffer,m_buffer+m_start,len);
        }else{
            memcpy(buffer,m_buffer+m_start,m_capacity - m_start);
            memcpy(buffer+(m_capacity - m_start),m_buffer,len - (m_capacity - m_start));
        }
        ret = true;
    }
    return ret;
}
bool CircleBuffer::fetch(char* buffer, const size_t len){
    bool ret = false;

    if(buffer == nullptr || len == 0){
        return  ret;
    }

    if(m_size >= len){
        if(m_capacity - m_start >= len){
            memcpy(buffer,m_buffer+m_start,len);
            m_start = m_start + len;
        }else{
            memcpy(buffer,m_buffer+m_start,m_capacity - m_start);
            memcpy(buffer+(m_capacity - m_start),m_buffer,len - (m_capacity - m_start));
            m_start = len - (m_capacity - m_start);
        }

        m_size = m_size - len;
        ret = true;
    }

    return ret;
}

void CircleBuffer::clear(){
    this->m_start = 0;
    this->m_end = 0;
    this->m_size = 0;
}

CircleBuffer::~CircleBuffer(){
    if(m_buffer){
        delete[] m_buffer;
        m_buffer = nullptr;
    }
}

}