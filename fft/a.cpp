#define ld long double
const ld pi=acos(-1);
struct cp{ld x,y;};
cp operator +(cp a,cp b){return (cp){a.x+b.x,a.y+b.y};}
cp operator -(cp a,cp b){return (cp){a.x-b.x,a.y-b.y};}
cp operator *(cp a,cp b){return (cp){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
cp cur[N];
void fft(cp *a,int n,int fl){
	for(int i=(n>>1),j=1;j<n;++j){
		if(i<j)swap(a[i],a[j]);
		int k;
		for(k=(n>>1);k&i;i^=k,k>>=1);i^=k;
	}
	for(int m=2;m<=n;m<<=1){
		cp w=(cp){cos(2*pi*fl/m),sin(2*pi*fl/m)};
		cur[0]=(cp){1,0};
		for(int j=1;j<(m>>1);j++)cur[j]=cur[j-1]*w;
		for(int i=0;i<n;i+=m)
			for(int j=i;j<i+(m>>1);++j){
				cp u=a[j],v=a[j+(m>>1)]*cur[j-i];
				a[j]=u+v;
				a[j+(m>>1)]=u-v;
			}
	}     
}
