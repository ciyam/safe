// Copyright (c) 2012 CIYAM Open Developers

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

//#define DEBUG

using namespace std;

const size_t num_rounds = 10000;

void harden( size_t& count, string& np, const vector< string >& table )
{
   for( size_t i = 0; i < np.size( ); i++ )
      count += ( size_t )np[ i ];
}

int main( int argc, char* argv[ ] )
{
   if( argc < 2 )
      cout << "usage: stretch [password]" << endl;
   else
   {
      string p( argv[ 1 ] );
      vector< string > table;

      ifstream inpf( "data", ios::in | ios::binary );

      if( !inpf )
      {
         cerr << "error: cannot open 'data' for input" << endl;
         return 1;
      }

      size_t count = 0;
      for( size_t i = 0; i < 255; i++ )
      {
         table.push_back( "" );
         for( size_t j = 0; j < 255; j++ )
         {
            char ch;
            inpf >> ch;

            ++count;
            table.back( ) += ch;

            if( inpf.eof( ) )
               break;
         }

         if( inpf.eof( ) )
            break;
      }

      if( count != 65025 )
      {
         cerr << "error: unexpected data size: " << count << endl;
         return 1;
      }

      count = 0;
      for( string::size_type i = 0; i < p.length( ); i++ )
         count += ( int )p[ i ];

      size_t modulus = count % 255;
#ifdef DEBUG
      cout << "modulus = " << modulus << endl;
#endif

      string rp( p );
      reverse( p.begin( ), p.end( ) );

      string np;
      count = 0;
      for( size_t i = 0; i < table[ modulus ].size( ); i++ )
      {
         char ch = table[ modulus ][ i ];
         switch( ch )
         {
            case '0':
            case '1':
            np += ch;
            break;

            case '2':
            np += p;
            break;

            case '3':
            np += rp;
            break;

            default:
            cerr << "error: unexpected data character '" << ch << "'" << endl;
            return 1;
         }

         for( size_t j = 0; j < num_rounds; ++j )
            harden( count, np, table );

         modulus = count % 255;
#ifdef DEBUG
         cout << "modulus now = " << modulus << endl;
#endif
         np += table[ modulus ][ 0 ];
      }

      cout << np;
   }

   return 0;
}

