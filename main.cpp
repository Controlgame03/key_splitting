#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_SECRET 100000
#define MIN_SECRET 10000
#define MAX_PEOPLE 5
#define MIN_PEOPLE 2

bool is_prime(int n)
{
    if(n == 1 || n == 0) return false;

    for(int i = 2; i < n; i++)
    {
        if(n % i == 0) return false;
    }
    return true;
}

vector<int> generate_prime(int size){
    vector<int> result;

    for(int i = 1; i <= size; i++)
    {
        if(is_prime(i))
        {       
            result.push_back(i);
        }
    }
    return result;
}

long long int inverse_element(long long int value, long long int module){
    for(int i = 1; i < module; i++){
        if((i * value) % module == 1){
            return i;
        }
    }
    return 0;
}

int main()
{
    int secret = 0;
    int n, k;

    cout << "-------------------------------------------------------------" << "\n";
    cout << "----------------------->sharing phase<-----------------------" << "\n";
    cout << "-------------------------------------------------------------" << "\n\n";
    cout << "input:" << "\n";
    cout << "please enter the secret (integer from 10000 to 100000): ";
    cin >> secret;

    if(secret > MAX_SECRET || secret < MIN_SECRET){
        cout << "error. the secret must be a number between 10000 and 100000" << endl;
        return 0;
    }

    cout << "please enter the number of users (integer from 2 to 5): ";
    cin >> n;

    if(n > MAX_PEOPLE || n < MIN_PEOPLE){
        cout << "error. the number of users must be a number between 2 and 5" << endl;
        return 0;
    }

    cout << "please enter the number of users needed to get the secret (integer from 2 to 5):";
    cin >> k;

    if(k > MAX_PEOPLE || k < MIN_PEOPLE){
        cout << "error. the number of users needed to get the secret must be a number between 2 and 5;" << endl;
        return 0;
    }
    
    if(n < k){
        cout << "error. the number of secret users cannot be greater than the number of users" << endl;
        return 0;
    }

    vector<int> primes = generate_prime(secret);
    vector<int> prime_parts;
    vector<int> value_parts;

    srand(time(0));
    for(int i = 0; i < n; i++){
        int index = rand() % (primes.size() - 1);
        double min_value = pow((double)secret, (double)pow(k, -1));
        double max_value = pow((double)secret, (double)pow(k - 1, -1));
        while(((double)primes[index] <= min_value) || ((double)primes[index] > max_value) || (find(prime_parts.begin(), prime_parts.end(), primes[index]) != prime_parts.end())){
            index = rand() % (primes.size() - 1);
        }
        prime_parts.push_back(primes[index]); 
    }

    cout << "\n";
    for(int i = 0; i < prime_parts.size(); i++){
        value_parts.push_back(secret % prime_parts[i]);
    }

    cout << "output:\n";
    for(int i = 0; i < n; i++){
        cout << "( x(" << i + 1<< ") = " << value_parts[i] << ", p(" << i + 1 << ") = " << prime_parts[i] << " )" << "\n"; 
    }

    cout << "\n-------------------------------------------------------------" << "\n";
    cout << "------------------->secret phase recovery<-------------------" << "\n";
    cout << "-------------------------------------------------------------" << "\n\n";
    
    cout << "input:\n";

    vector<int> positions;
    positions.push_back(rand() % n);
    for(int i = 1; i < k; i++){
        int new_index = rand() % n;
        while(find(positions.begin(), positions.end(), new_index) != positions.end()){
            new_index = rand() % n;
        }

        positions.push_back(new_index);
        int tmp = prime_parts[i];
        prime_parts[i] = prime_parts[new_index];
        prime_parts[new_index] = tmp;

        tmp = value_parts[i];
        value_parts[i] = value_parts[new_index];
        value_parts[new_index] = tmp;
    }

    for(int i = 0; i < k; i++){
        cout << "( x(" << i + 1 << ") = " << value_parts[i] << ", p(" << i + 1 << ") = " << prime_parts[i] << " )" << "\n"; 
    }

    long long int result_secret = 0;
    long long int module = 1;
    
    for(int i = 0; i < k; i++){
        module *= prime_parts[i];
    }

    for(int i = 0; i < k; i++){
        long long int first = (module / prime_parts[i]) % module;
        long long int second = value_parts[i] % module;
        long long int third = inverse_element(module / prime_parts[i], prime_parts[i]) % module;
        result_secret += ((first * second * third) % module);    
    }
    result_secret = result_secret % module;

    cout << "\noutput:\nsecret = " << result_secret << "\n\n" << endl;
    return 0;
}