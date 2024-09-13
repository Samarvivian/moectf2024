#include<stdio.h>

int main()
{
	//unsigned int enc[12] = {0xA3, 0x69, 0x96, 0x26, 0xBD, 0x78, 0x0B, 0x3D, 0x9D, 0xA5, 0x28, 0x62};
	unsigned int enc[4] = {0x3d0b78bd,0x6228a59d,0x269669a3,1623250656};
    unsigned int key[4] = {2,0,2,4};
	int i, j;
	long sum = 0, delta = 0x33004445;
    // 解码
	for(i=0;i < 4;i+=2){
		sum =  0-(32 * delta);
		for(j = 0; j < 32; j++) {
			enc[i+1] -= (((enc[i] >> 5) ^ (16 * enc[i])) + enc[i]) ^ (key[((sum >> 11) & 3)] + sum);
			sum += delta;
			enc[i] -= ((((enc[i+1] >> 5) ^ (16 * enc[i+1])) + enc[i+1]) ^ key[sum & 3] + sum);
		}
	}
    // 打印
	for (i = 0; i < 4; i++)
	{
		printf("%d ",enc[i]);
		for (j = 0; j<=3; j++)
		{
			printf("%c", (enc[i] >> (j * 8)) & 0xFF);
		}
	}

	return 0;
}
