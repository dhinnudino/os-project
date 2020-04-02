#include <iostream>
#include "pthread.h"

using namespace std;

struct station{
    int waiting_passengers;
    pthread_mutex_t passenger_lock;
    pthread_mutex_t train_lock;
};

void station_init(struct station *station);
void station_on_board(struct station *station);
void station_load_train(struct station *station, int count);
void station_wait_for_train(struct station *station);

void station_init(struct station *station)
{
	station->waiting_passengers = 0;

	if(pthread_mutex_init(&station->passenger_lock, NULL) != 0 && pthread_mutex_init(&station->train_lock, NULL) != 0){
        cout << "Caution! Error!" << endl;
        cout << "This station has been Destroyed." << endl;
	}
}

void station_load_train(struct station *station, int count){
    if( count == 0 || station->waiting_passengers == 0) 
        return;

    do{
        pthread_mutex_unlock(&(station->train_lock)); 
        count--;
    }while( count > 0 && station->waiting_passengers > 0 );

}

void station_wait_for_train(struct station *station){
    pthread_mutex_lock(&(station->passenger_lock));
    station->waiting_passengers++;
    pthread_mutex_unlock(&(station->passenger_lock));

    pthread_mutex_lock(&(station->train_lock));
    station_on_board(station);
}

void station_on_board(struct station *station){
    if( station->waiting_passengers <= 0 ) 
        return;
    pthread_mutex_lock(&(station->passenger_lock));
    station->waiting_passengers--;
    pthread_mutex_unlock(&(station->passenger_lock));
}

int main(){

    return 0;
}
