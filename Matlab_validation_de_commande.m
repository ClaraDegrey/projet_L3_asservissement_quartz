
% Charger les données du fichier
mesure = load('fichier.dat');

% Calculer la moyenne de la première colonne
mean_col1 = mean(mesure(:,1));

% Tracer la commande
subplot(2,1,1);
plot(mesure(:,1) - mean_col1, '-');
ylabel('Commande');
xlabel('Temps (s)');

% Tracer la fréquence
subplot(2,1,2);
plot(mesure(:,3) - mean(mesure(:,3)), '-');
ylabel('Fréquence (Hz)');
xlabel('Temps (s)');
