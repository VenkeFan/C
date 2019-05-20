#include <stdio.h>

/*
	一、题目

　　求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数。
*/

long CountOne2(long n) {
    long count = 0; // 1的个数
    long i = 1;  // 当前位
    long current = 0,after = 0,before = 0;

    while((n / i) != 0) {
        before = n / (i * 10); // 高位
        current = (n / i) % 10; // 当前位
        after = n - (n / i) * i;  // 低位

        if (current == 0)
            //如果为0,出现1的次数由高位决定,等于高位数字 * 当前位数
            count = count + before * i;
        else if(current == 1)
            //如果为1,出现1的次数由高位和低位决定,高位*当前位+低位+1
            count = count + before * i + after + 1;
        else if (current > 1)
            // 如果大于1,出现1的次数由高位决定,（高位数字+1）* 当前位数
            count = count + (before + 1) * i;
        //前移一位
        i = i * 10;
    }
    return count;
}

int NumberOf1Between1AndN_Solution(int n){
    int count=0;

    for(int i = 1; i <= n; i *= 10){
        int a = n / i; // 高位
        int b = n % i; // 低位
        count += (a+8) / 10 * i;
        if(a % 10 == 1){
            count += b + 1;
        }
    }
    return count;
}

int main() {
	int a = 2^4^5^6;
	printf("%d\n", a);
}