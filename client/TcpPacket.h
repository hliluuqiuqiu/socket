#ifndef TCP_PACKET_H_SQH
#define TCP_PACKET_H_SQH
namespace sqh{
class TcpPacket{
private:    
    int m_header_len;
    int m_type_len;
    int m_body_len;
    int m_bodyLen_len;
    char* m_header;
    char* m_type;  
    char* m_body;
protected:
TcpPacket(int hLen,int tLen,int bLen, int bodyLen_len);
bool construct();
public:
    static TcpPacket* NewInstance(int hLen,int tLen,int bLen, int bodyLen_len);
    const int getHeaderLen();
    const int getTypeLen();
    const int getBodyLen();
    const int getBodyLenSize();
   // const int getHeaderLen();

    void setHeaderLen(int hLen);
    void setTypeLen(int tLen);
    void setBodyLen(int bLen);

    char* getHeader();
    char* getType();
    char* getBody();



    virtual ~TcpPacket();
};
}
#endif