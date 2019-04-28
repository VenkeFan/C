/*
一、题目

　　输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

二、思路

　　　　我们以三个字符abc为例来分析一下求字符串排列的过程。首先我们固定第一个字符a，求后面两个字符bc的排列。当两个字符bc的排列求好之后，我们把第一个字符a和后面的b交换，得到bac，接着我们固定第一个字符b，求后面两个字符ac的排列。现在是把c放到第一位置的时候了。记住前面我们已经把原先的第一个字符a和后面的b做了交换，为了保证这次c仍然是和原先处在第一位置的a交换，我们在拿c和第一个字符交换之前，先要把b和a交换回来。在交换b和a之后，再拿c和处在第一位置的a进行交换，得到cba。我们再次固定第一个字符c，求后面两个字符b、a的排列。

　　既然我们已经知道怎么求三个字符的排列，那么固定第一个字符之后求后面两个字符的排列，就是典型的递归思路了
*/


#include <stdio.h>

void permutationStr(char p[], int depth, int length) {
	if (depth == length) {
		printf("%s", p);
		printf("\n");
		return;
	}
	char c;
	for (int i = depth; i < length; i++){
		c = p[depth]; p[depth] = p[i]; p[i] = c;
		permutationStr(p, depth+1, length);
		c = p[depth]; p[depth] = p[i]; p[i] = c;
	}
}

int main() {
	char source[3] = "abc";
	permutationStr(source, 0, 3);

	return 0;
}