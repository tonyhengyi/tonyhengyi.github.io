



```cpp
#include<graphics.h>
#include<iostream>

using namespace std;

int main() {
	initgraph(1280, 720);
	int x = 300;
	int y= 300;

	BeginBatchDraw();

	while (true) {
		ExMessage mcg;
		while (peekmessage(& mcg)) {
			if (mcg.message == WM_MOUSEMOVE) {
				x = mcg.x;
				y = mcg.y;
			}
		}
		cleardevice();
		solidcircle(x, y, 100);
		FlushBatchDraw();
	}
	
	EndBatchDraw();
	return 0;
}
```

