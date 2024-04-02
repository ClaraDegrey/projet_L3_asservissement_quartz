% Définir les valeurs de résistance et de condensateur
R = [3000 1000 5100 2000 22 5600]; % Résistance en ohms
C = [1e-6 100e-9 12e-12 15e-12 1e-9 20e-12]; % Condensateur en farads

% Initialiser la matrice pour stocker les fréquences calculées
frequencies = zeros(length(R), length(C));

% Boucle pour calculer la fréquence pour chaque combinaison de R et C
for i = 1:length(R)
    for j = 1:length(C)
        % Calcul de la fréquence
        f = 1 / (2 * pi * R(i) * C(j));
        % Stockage de la fréquence dans la matrice
        frequencies(i, j) = f;
        % Affichage de la valeur de R et C correspondant à la fréquence calculée
        disp(['Pour une fréquence de ', num2str(f), ' Hz, R = ', num2str(R(i)), ' ohms et C = ', num2str(C(j)), ' farads']);
    end
end

C_ideal = 1/(5600 * 2 *pi * 17000);

