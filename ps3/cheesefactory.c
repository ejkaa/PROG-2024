#include <stdio.h>

#define M_PI 3.141592653

struct sphere{
    double r;
    double x;
    double y;
    double z;
};

double pov(double number, int power);
double volume(double r, double h);


int main(){
    int m, s;
//    double v1 = 0;
    scanf("%d %d", &m, &s);

    if(s == 1){
        printf("%.7lf\n", (double)100);
        return 0;
    }

    if(m == 0){
        for (int i = 0; i < s; ++i){
            printf("%.7lf\n", (double)100/s);
        }
        return 0;
    }


    struct sphere list[m];
    for (int i = 0; i < m; ++i){
        scanf("%lf %lf %lf %lf", &list[i].r, &list[i].x, &list[i].y, &list[i].z);
        list[i].r /= (double)1000;
        list[i].x /= (double)1000;
        list[i].y /= (double)1000;
        list[i].z /= (double)1000;
    }

//    for (int i = 0; i < m; ++i){
//        printf("%lf %lf %lf %lf\n", list[i].r, list[i].x, list[i].y, list[i].z);
//    }

    double V = (double)1000000, V_mid, zh = (double)100, zl = (double)0;

//    printf("%lf\n", pow(10.00000, 3));

    for (int i = 0; i < m; i++){
        //double trash = 4*(M_PI)/3;
        V -= (double)4*(M_PI)/(double)3 * (pov(list[i].r, 3));
    }
    V_mid = V/(double)s;

//    printf("%lf\n", V);


    for (int i = 0; i < s; ++i) {
        double max = 100, min = zl;

        while(max >= min){
            zh = (max + min) / (double)2;
            double V_loc = (zh - zl) * (double)100 * (double)100;

            for (int j = 0; j < m; ++j) {
                if((list[j].z + list[j].r) > zl && (list[j].z - list[j].r) < zh){
                    if(zh >= list[j].z + list[j].r && zl <= list[j].z - list[j].r){
                        V_loc -= (double)4*(M_PI)/(double)3 * pov(list[j].r, 3);
                    }

                    else if((zh < list[j].z + list[j].r && zh > list[j].z - list[j].r) && (zl <= list[j].z - list[j].r)){
                        double h = zh - (list[j].z - list[j].r);
                        V_loc -= volume(list[j].r, h)/*(M_PI * pov(h, 2) * (3*list[j].r - h))/3*/;
                    }

                    else if((zh >= list[j].z + list[j].r) && (zl > list[j].z - list[j].r && zl < list[j].z + list[j].r)){
                        double h = list[j].z + list[j].r - zl;
                        V_loc -= volume(list[j].r, h)/*(M_PI * pov(h, 2) * (3*list[j].r - h))/3*/;
                    }

                    else if(zh < list[j].z + list[j].r && zl > list[j].z - list[j].r){
                        double h1 = list[j].z + list[j].r - zh;
                        double h2 = zl - (list[j].z - list[j].r);

                        V_loc -= (double)4*(M_PI)/(double)3 * pov(list[j].r, 3) - volume(list[j].r, h1) - volume(list[j].r, h2)
                            /*(M_PI * h1*h1 * (3*list[j].r - h1) + M_PI * h2*h2 * (3*list[j].r - h2))/3*/;
                    }
                }
            }


            if (((max - min) < 0.000000001)){
                printf("%.9lf\n", zh - zl);
//                v1 += (zh - zl);
                zl = zh;
                break;
            }

            else if (V_loc > V_mid){
                max = zh;
                //     printf ("%f %f\n", time_sum, k);
            }

            else{
                min = zh;
            }
        }
    }

//    printf("%lf\n", v1);


}

double pov(double number, int power){
    if(power == 2)
        return number*number;

    if(power == 3)
        return number*number*number;

    return 0;
}

double volume(double r, double h){
    double m = M_PI * (pov(h, 2)*r - pov(h, 3)/(double)3);

    return m;
}