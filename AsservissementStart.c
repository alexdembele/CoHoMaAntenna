/*-------------Code arduino------------------
@Dembélé Alex 

Ce programme n'est pas fini. Il commence le code pour asservir les antennes avec des servomoteurs
La communication avec avec l'opérateur/Interface Homme Machine est censé se faire avec rosArduino
Pour apprendre en accéléré rosArduino, regardé les vidéos concernées du readME

Attention: Régler initialisation des moteurs pour définir le 0 des angles*/




#include <Servo.h>
#include <math.h>
/*#include <ros.h> // Cette bibliothèque est à installer si ce n'es pas déja fait. Cela peut se faire dans le programme arduino etsa gestion des bibliothèques. Il faut aussi que ros et pyserial soient installés sur votre ordinateur
#include <std_msgs/Int8.h> //Format des messages échangés (il faudra surement le changer pour s'échanger des listes de nombre

ros::NodeHandle nh;
void messageCb(const std_msgs::Int8& toggle_msg){
  if(toggle_msg.data==4)
  {
    digitalWrite(13,HIGH-digitalRead(13));
  }
}

ros::Subscriber<std_msgs::Int8> sub("chatter", messageCb); //Subscriber pour communiquer et récupérer les informations de l'IHM
*/
Servo servoDirection;  // Servomoteur dirigeant la direction ("Nord Sud Est Ouest"), ou le lacet en langage maritime
Servo servoInclinaison; // Servomoteur dirigeant l'inclinaison de l'antenne("Haut Bas")

float theta_direction;
float theta_inclinaison;

float x_vab;
float y_vab;
float z_vab;
float angle_vab;

float x_drone;
float y_drone;
float z_drone;

float x_husky;
float y_husky;
float z_husky;

float hauteur ; //hauteur du robot
float distance; //distance vab robot
float angle_direction;
float angle_inclinaison;

bool selection; //true focus drone, false focus husky

float K_inclinaison; //gain asservissement
float K_direction;

float norme(float a_x, float a_y) //Fonction retournant la norme d'un vecteur a=(a_x, a__y). 
{
  return sqrt(a_x*a_x+a_y*a_y);
}

float angleVecteur(float a_x, float a_y, float b_x, float b_y) // Détermine l'angle entre deux vecteurs a=(a_x, a__y) et b=(b_x, b__y). Cette fonction est présente car les fonctions atan ou atan2 n'ont pas forcément les bonnes plages angulaires de sortie
{
  float dot=a_x * b_x + a_y *b_y; //produit scalaire
  float norma=norme(a_x,a_y);
  float normb=norme(b_x,b_y);
  float prodVectoriel=(a_x*b_y-a_y*b_x);//produit vectoriel
  if (prodVectoriel>=0)
    {
        return (180/M_PI)*acosf(dot/(norma*normb));
    }
    else
    {
        return -(180/M_PI)*acosf(dot/(norma*normb));
    }
}

void setup() {
  servoDirection.attach(9);  // attaches the servo on pin 9 to the servo object
  servoInclinaison.attach(10);
  pinMode(LED_BUILTIN, OUTPUT);
  //nh.initNode();
  //nh.subscribe(sub);

}

void loop() {
  //--Communication avec ordi--
  //nh.spinOnce();



  //--Acquerir position drone et husky--


   
  //--selectionner target--

  if(selection) //asservissement sur drone
  {
    //acquisition geometrie
    hauteur=z_drone-z_vab;
    distance=norme(x_drone-x_vab,y_drone-y_vab);
    angle_inclinaison=atan(hauteur/distance);
    angle_direction=angleVecteur(x_vab,y_vab,x_drone,y_drone); // limitée dans une plage angulaire par atan.
    angle_direction-=angle_vab;


    //Asservissement

    //theta_inclinaison+=K_inclinaison(angle_inclinaison-theta_inclinaison);
    //theta_direction+=K_direction(angle_direction-theta_direction);

    //servoDirection.write(theta__direction);
    //servoInclinaison.write(theta_inclinaison);

  }

  else
  {
    //acquisition geometrie
    hauteur=z_husky-z_vab;
    distance=norme(x_husky-x_vab,y_husky-y_vab);
    angle_inclinaison=atan(hauteur/distance);
    angle_direction=angleVecteur(x_vab,y_vab,x_husky,y_husky);
    angle_direction-=angle_vab;


    //Asservissement

    //theta_inclinaison+=K_inclinaison(angle_inclinaison-theta_inclinaison);
    //theta_direction+=K_direction(angle_direction-theta_direction);

    //servoDirection.write(theta__direction);
    //servoInclinaison.write(theta_inclinaison);
  }


  delay(500); // A régler par test pour que l'asservissement ne soit ni trop nerveux ni trop lent
}
