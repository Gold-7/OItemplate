int exgcd(int a, int b, int &c, int &d, int &e) {
	if (b == 0) {
		c = a;
		d = 1;
		e = 0;
		return ;
	}
	exgcd(b, a % b, c, e, d);
	e -= a / b * d;
}
