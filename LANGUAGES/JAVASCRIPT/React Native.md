# Project architecture
Exemple:
```bash
my-movie-app/
├── App.js
├── package.json
├── node_modules/
├── src/
│   ├── components/
│   │   ├── Movie.js
│   │   └── ...
│   ├── screens/
│   │   ├── HomeScreen.js
│   │   └── ...
│   └── utils/
│       ├── api.js
│       └── ...
├── package-lock.json
├── package.json
├ ....
```

**App.js** est le point d'entrée de l'application, qui contient le code principal pour initialiser et configurer l'application.

**package.json** est le fichier de configuration de npm qui définit les dépendances, les scripts et les métadonnées de l'application.

**node_modules** est le répertoire où sont stockées les dépendances installées via npm.

**src** est un répertoire qui contient tout le code source de l'application.

**components** est un répertoire qui contient des composants réutilisables qui peuvent être utilisés dans différentes parties de l'application.

**screens** est un répertoire qui contient des composants qui représentent des écrans distincts de l'application.

**utils** est un répertoire qui contient des utilitaires, tels que des fonctions pour effectuer des appels d'API ou pour effectuer des opérations réutilisables dans l'application.

**package-lock.json** est un fichier généré automatiquement par npm lors de l'installation ou de la mise à jour d'un paquet. Ce fichier est utilisé pour stocker les détails précis de chaque paquet installé dans un projet, y compris les informations sur les versions exactes des paquets, leurs dépendances et les chemins d'installation. En d'autres termes, package-lock.json enregistre une "instantané" des dépendances de votre projet et garantit que chaque membre de l'équipe travaillant sur le projet installe exactement les mêmes versions de paquets, ce qui aide à garantir la cohérence et la fiabilité de l'application.
package-lock.json est utilisé pour déterminer les dépendances exactes d'un projet lors de l'installation ou de la mise à jour des paquets, en utilisant une logique de résolution de dépendances appelée "algorithme de résolution de dépendances à deux niveaux". Cela garantit que les mêmes versions exactes de tous les paquets sont installées, même si certaines dépendances sont partagées entre plusieurs paquets.

# Help
Rename a existing react native project:
- rename the folder
- open package.json and change the name project at the beginning of the file
# Troubleshooting

Stuck at:
```bash
$ npx expo start
Starting project at C:\Users\sesa622412\Documents\Other projects\ski_save\my-react-app
```
Not really stuck, it is a network error, dependancies cannot be checked, you can skip it by:
```shell
$ npx expo start --offline
Starting project at C:\Users\sesa622412\Documents\Other projects\ski_save\my-react-app
Skipping dependency validation in offline mode
Starting Metro Bundler
```