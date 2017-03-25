#include "comm.h"
#include <string.h>

int main() {
	char s[100] = "data=asdasd;x='q%38we'";
	char file[100] = "Hello every one.";
	send_post("192.168.0.169/pqhuy98/Rasp/test.php",s,file,strlen(file));
}