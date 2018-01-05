// Copyright (c) 2012-2018 CIYAM Developers

#include <string>
#include <fstream>
#include <iostream>

const char* const c_outfile = "x";
const char* const c_password = "password";

const char* const c_address_prefix = "Address: ";
const char* const c_privkey_prefix = "Privkey: ";

using namespace std;

int main( int argc, char* argv[ ] )
{
   cout << c_password << endl;

   bool is_second = false;
   if( argc > 1 && string( argv[ 1 ] ) == "2" )
      is_second = true;

   string str;
   while( getline( cin, str ) )
   {
      if( is_second )
         cout << str << '\n';
      else if( str.find( c_address_prefix ) == 0 )
      {
         ofstream outf( c_outfile );
         outf << str << '\n' << endl;
      }
      else if( str.find( c_privkey_prefix ) == 0 )
         cout << str << endl;
   }
}

