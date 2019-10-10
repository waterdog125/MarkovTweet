#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
class markov {
public:
    void create( std::string file, int keyLen, int chars ) {
        std::ifstream f( file.c_str(), std::ios_base::in );
        fileBuffer = std::string( ( std::istreambuf_iterator<char>( f ) ), std::istreambuf_iterator<char>() );
        f.close();
        if( fileBuffer.length() < 1 ) return;
        createDictionary( keyLen );
        createText( chars - keyLen );
    }
private:
    void createText( int c ) {
        std::string key, first, second;
        size_t next, pos;
        std::map<std::string, std::vector<std::string> >::iterator it = dictionary.begin();
        std::advance( it, rand() % dictionary.size() );
        key = ( *it ).first;
        int charCounter =0;
        std::cout << key;

        while( charCounter < c+1 ) {
            
            std::vector<std::string> d = dictionary[key];
            
            if( d.size() < 1 ) break;
            second = d[rand() % d.size()];
            if( second.length() < 1 ) break;
            std::cout << " " << second;
            if( --c < 0 ) break;
            next = key.find_first_of( 32, 0 );
            first = key.substr( next + 1 );
            key = first + " " + second;
            for(int i=0; i<key.length();i++){
                charCounter+=1;
                key[i++];
                //std::cout<< key.length();
                if (key[i]==NULL){
                    break;
                }
            }
        }
        std::cout << "\n";
    }
    void createDictionary( int kl ) {
        std::string w1, key;
        size_t wc = 0, pos, textPos, next;
        next = fileBuffer.find_first_not_of( 32, 0 );
        if( next == -1 ) return;
        while( wc < kl ) {
            pos = fileBuffer.find_first_of( ' ', next );
            w1 = fileBuffer.substr( next, pos - next );
            key += w1 + " ";
            next = fileBuffer.find_first_not_of( 32, pos + 1 );
            if( next == -1 ) return;
            wc++;
        }
        key = key.substr( 0, key.size() - 1 );
        while( true ) {
            next = fileBuffer.find_first_not_of( 32, pos + 1 );
            if( next == -1 ) return;
            pos = fileBuffer.find_first_of( 32, next );
            w1 = fileBuffer.substr( next, pos - next );
            if( w1.size() < 1 ) break;
            if( std::find( dictionary[key].begin(), dictionary[key].end(), w1 ) == dictionary[key].end() )
                dictionary[key].push_back( w1 );
            key = key.substr( key.find_first_of( 32 ) + 1 ) + " " + w1;
        }
    }
    std::string fileBuffer;
    std::map<std::string, std::vector<std::string> > dictionary;
};
int main( int argc, char* argv[] ) {
    srand( unsigned( time( 0 ) ) );
    markov m;
    m.create(std::string("uscon.txt"), 3, 400);

    return 0;
}
