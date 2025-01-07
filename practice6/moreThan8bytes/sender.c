#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>

#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int main(void) 
{
        int socketCANDescriptor;
        struct sockaddr_can addr;
        struct ifreq ifr;
        struct can_frame frame;

        char inputString[128];
        char sendMessage[8];        
        
        int packetTotal=0;                 // Number of packets to send
        int lastPacketSize=0;              // Size of last packet

        int i;
        
        
        printf("SocketCAN Sender\n");

        if ((socketCANDescriptor = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
                perror("Socket creation failed.");
                return -1;
        }

        strcpy(ifr.ifr_name, "can0" );
        ioctl(socketCANDescriptor, SIOCGIFINDEX, &ifr);
        memset(&addr, 0, sizeof(addr));
        
        addr.can_family = AF_CAN;        
        addr.can_ifindex = ifr.ifr_ifindex;

        if (bind(socketCANDescriptor, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("Bind failed");
                return -1;
        }

        while(1) {                
                printf("\nEnter your text: ");
                fgets(inputString, 128, stdin);
                printf("Your text: %s", inputString);                
                printf("Input Length = %d\n", (int)strlen(inputString));
                int len=(int)strlen(inputString);
                // Insert your code here to send inputString using write() function
                // You may need to use the above declared variables "packetTotal" and "lastPacketSize"
                lastPacketSize=0;
                packetTotal=0;
                frame.can_id = 0x555;
                if(len<=8){
                        frame.can_dlc = len;
                        memcpy(frame.data, (char *)inputString, len);
                        if (write(socketCANDescriptor, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                                perror("Write failed");
                                return -1;
                        }
                        packetTotal++;
                }
                else{
                        while(len>8){
                                frame.can_dlc = 8;
                                memcpy(frame.data, (char *)inputString+(packetTotal*8), 8);
                                if (write(socketCANDescriptor, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                                        perror("Write failed");
                                        return -1;
                                }
                                packetTotal++;
                                len-=8;
                        }
                        if(len!=0){
                                frame.can_dlc = len;
                                memcpy(frame.data, (char *)inputString+(packetTotal*8), len);
                                if (write(socketCANDescriptor, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                                        perror("Write failed");
                                        return -1;
                                }
                                packetTotal++;
                        }
                }
                
                lastPacketSize=len;
                printf("Number of Packets to send = %d\n",packetTotal);
                printf("Size of Last Bytes to send = %d\n",lastPacketSize);

                if (strcmp(inputString, "q\n") == 0) break;

        }
        printf("\nQUIT COMMNAD!\n");
        if (close(socketCANDescriptor) < 0) {
                perror("Close failed");
                return -1;
        }

        return 0;
}
