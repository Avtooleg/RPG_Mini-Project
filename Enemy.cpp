
#include "Enemy.hpp"
void Enemy::roam(){
    {
        int i =4;//i число мув поинтов у моба
        if( i > 0){
            int a= get_random_int(1,4);
           
           if(a==1){
 
                direction.y = -1;
                move(direction);
               i=i-1;
                break;
            }
           if(a==2) {
                direction.y = 1;
                move(direction);
               i=i-1;
                break;
            }
           if(a==3) {
                direction.x = -1;
                move(direction);
               i=i-1;
                break;
            }
            if(a==4){
                direction.x = 1;
                move(direction);
                i=i-1;
                break;
            }
        else{
               break
           }
}
