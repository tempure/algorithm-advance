#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char b[ 1000005 ];

int main( void ) {
    scanf( "%s", b );
    reverse( b, b + strlen( b ) );

    int cnt = 0;

    for ( int i = 0; b[i]; ++i ) {
        if ( b[i] == '0' ) ++cnt;
        else if ( b[i] == '1' && b[i + 1] != 0 ) { b[i] = '0'; b[i + 1] = max( b[i + 1], '0' ) + 1; ++cnt; --i; }
        else if ( b[i] == '2' ) { b[i] = '0'; b[i + 1] = max( b[i + 1], '0' ) + 1; --i; };
    }

    printf( "%d\n", cnt );
    return 0;
}