
#include <iostream>
#include <iomanip>

using namespace std;

unsigned int* raw(int length,unsigned int* a){
  unsigned int* ans = new unsigned int[length * 32];
  for(int i = 0;i < length;i++){
      for(int j = 0;j < 32;j++){
        ans[i * 32 + j] = ((a[i] >> j) & 1);
      }
  }
  return ans;
}

unsigned int* deraw(int length,unsigned int *b){
  unsigned int* ans = new unsigned int[length / 32];
  for(int i = 0;i < length;i++){
    ans[i / 32] |= (b[i] << (i % 32));
  }
  return ans;
}

int main()
{
  int size;

  cin >> size;

  unsigned int* a = new unsigned int[size / 16]; // <- input tab to encrypt
  unsigned int* b = new unsigned int[size / 16]; // <- output tab

  unsigned int* a0 = new unsigned int[size / 32]; // <- first half of a
  unsigned int* a1 = new unsigned int[size / 32]; // <- second half of a
 
  for (int i = 0; i < size / 16; i++) {   // Read size / 16 integers to a
    cin >> hex >> a[i];
    if(i < size / 32){
      a0[i] = a[i];
    }else{
      a1[i - size / 32] = a[i];
    }
  }

  unsigned int* raw_a0 = raw(size / 32,a0);
  unsigned int* raw_a1 = raw(size / 32,a1);
  
  unsigned int* raw_b = new unsigned int[size * 2]; // <- raw output

  for(int i = 0;i < size * 2;i++){
    raw_b[i] = 0;
  }

  for (int i = 0; i < size / 16; i++) {   // Write size / 16 zeros to b
    b[i] = 0;
  }	
 
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) {
      raw_b[i + j] ^= ( (raw_a0[i]) *
		                  (  raw_a1[j]));   // Magic centaurian operation
  }

  b = deraw(2 * size - 1,raw_b);
 
  for(int i = 0; i < size / 16; i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << setfill('0') << setw(8) << hex << b[i];       // print result
  }
  cout << endl;

 /* 
    Good luck humans     
 */
  return 0;
}
