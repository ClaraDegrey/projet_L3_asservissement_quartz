Projet de fin de Licence3 d'asservissment d'un quartz
Le code dans le fichier pmw permet d'envoyer un signal créneau avec un rapport cyclique variable
Les codes dans le fichier freq_en_fonction_de_pwm permettent d'observer la variation de la fréquence du quartz selon la valeir du rapport cyclique du signal pwm
Le code dans le dossier compteur_1s permet de lire des valeurs d'ISR lorsqu'on envoie un pulse toutes les 1 seconde
Le code dans le dossier communication permet de communiquer au microcontrolleur en utilisant la bibliotheque LUFA
Le code pid permet de corriger la fréquence du quartz avec un correcteur pid
Le code Valeurs_R_et_C_pour_fc permet de trouver pour quelles valeurs de resistance et de condensateur poir faire un filtre passe bas dont la frequence de coupure se situe entre la frequence de la pwm et le taux de rafraichissement de l'information
Le code Matlab proj permet de calculer la valeur moyenne de la PWM et de calculer les paramètres R et C du filtre RC
