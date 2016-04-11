#include <stdio.h>
#include <assert.h>
#include <string.h>
 
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("0.in","r",stdin);
	freopen("0.out","w",stdout);
	#endif
	int T;
	scanf("%d",&T);
	while(T--)
	{
		char s[111];
		scanf("%s",s);
		int L=strlen(s);
		int ans=0;
		for(int i=0;i<L;i++)
		{
			char c=s[i];
			if(c=='B') ans+=2; else
				if(c=='A' || c=='D' || c=='O' || c=='P' || c=='Q' || c=='R') ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
//ABCDEFGHIJKLMNOPQRSTUVWXYZ
 