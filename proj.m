clear all;
clc;
V = 5; %valeur d'amplitude
deg_lib = 1024; %degré de liberté
points = zeros(1, deg_lib); %vecteur de longueur 1024
for i = 1:deg_lib
    alpha = i / deg_lib;
    Vmoy = alpha * V; %valeur moyenne calculé
    points(i) = Vmoy;
end
plot(points);
xlabel('nombre de point');
ylabel('Valeur moyenne');
%%
R = [3000 1000 5100 2000 22 5600];
C = [1e-6 100e-9 12e-12 15e-12 1e-9 20e-12];
frequence = zeros(length(R), length(C)); % vecteur de stockage de valeur

for i = 1:length(R)
 for j = 1:length(C)
 f = 1 / (2 * pi * R(i) * C(j)); %calcul de fc
 frequence(i, j) = f;
 disp(['Pour une fréquence de ', num2str(f), ' Hz, R = ', num2str(R(i)), ' ohms et C = ', num2str(C(j)), ' farads']);
 end
end
C_ideal = 1/(5600 * 2 *pi * 17000);
