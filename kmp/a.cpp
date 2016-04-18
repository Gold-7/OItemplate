next[1] = 0;
for (int i = 2; i <= n; i++){
	int j = next[i - 1];
	while(j&&p[j+1]!=p[i])j=next[j];
	if(p[j+1]==p[i])j++;
	next[i]=j;
}
