#ifndef CIRCLEBUFFER_H_SQH
#define CIRCLEBUFFER_H_SQH
namespace sqh{
class CircleBuffer{
private:
char* m_buffer;
size_t m_capacity;
size_t m_size;
size_t m_start;
size_t m_end;
CircleBuffer(int capacity);
bool construct();
public:
static CircleBuffer* NewInstance(size_t capacity);
bool set(char* data , const size_t len);
bool get(char* buffer, const size_t len);
bool fetch(char* buffer, const size_t len);

size_t size(){
    return m_size;
}
void clear();
~CircleBuffer();
};

}
#endif
