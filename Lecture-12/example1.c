int function(int a, int b, int c) {
    int buffer1[2];
    int buffer2[4];
    buffer1[0] = 0;
    buffer1[1] = a;
    buffer2[0] = b;
    buffer2[3] = c;
    return 0;
}

int main() {
    function(1,2,3);
    return 0;
}

