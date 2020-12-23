#define BASE 0x40000000

int main(){
	*((int*)BASE) = 0x7fff;
}
