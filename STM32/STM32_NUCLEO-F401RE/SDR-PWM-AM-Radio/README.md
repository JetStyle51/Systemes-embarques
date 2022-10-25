# Minuterie, PWD et émission radio AM

Ref : https://01001000.xyz/2020-10-24-Tutorial-STM32CubeIDE-Timers-PWM-AM-Radio/

Mesurer, surveiller et réagir au passage du temps dans les systèmes embarqués est une exigence omniprésente. 
Par exemple, vous pouvez décider de basculer une sortie toutes les millisecondes. 
Vous pouvez être chargé d'implémenter un système qui échantillonne un ADC une fois par seconde. 
Vous voudrez peut-être modifier votre main()'s while(1)pour qu'il comporte un délai tel qu'il devienne une boucle avec une période fixe.

Pour y parvenir, vous devez maîtriser l'un des périphériques les plus utiles que vous rencontrerez dans vos microcontrôleurs : les timers. 
Ce sont des compteurs intégrés qui mesurent le passage du temps en fonction du comptage des impulsions d'horloge du microcontrôleur 
(vous pouvez également les faire compter d'autres choses, par exemple des impulsions sur une broche externe).

La configuration des minuteries, cependant, peut être un peu délicate, en particulier dans les microcontrôleurs aussi performants que la série STM32F. 
Donc, dans ce troisième tutoriel utilisant STM32CubeIDE, je vais expliquer rapidement comment nous pouvons commencer avec certains des cas d'utilisation les plus courants, 
et je terminerai avec une application de démonstration (très idiote) où nous (ab) utilisons une minuterie pour produire un signal radio AM.


## Mise en place du projet :

L'outil de configuration de périphérique est l'endroit où vous configurez exactement quelles broches/périphériques sont activés et quels sont leurs paramètres. Pour l'instant nous allons le laisser à ses valeurs par défaut, mais notons rapidement le matériel dont nous disposons :
![Image_1](https://01001000.xyz/assets/img/cubeide-timers/available-hardware.png)

Comme vous pouvez le voir, il y a un bouton-poussoir (appelé B1) à la broche PC13, une LED appelée LD2 à la broche PA5 et un UART TX/RX à PA2/PA3 qui se connecte au port COM virtuel du programmeur.

Pour l'instant, c'est tout ce dont nous aurons besoin. Alors, passons à la fenêtre de code. Naviguez à l'aide de l'explorateur de projets à gauche vers main.c.

## Faire clignoter une LED à l'aide de HAL_Delay()

Avant de commencer à jouer avec les périphériques de minuterie eux-mêmes, commençons par les bases : nous allons d'abord faire clignoter cette LED intégrée. Ensuite, nous jouerons avec les minuteries et verrons comment elles peuvent être rendues utiles.

À l' intérieur main.c, dirigez-vous vers l' while(1)intérieur main(). Pour rappel, pour ces fichiers générés automatiquement, vous ne devez introduire de code que dans les zones marquées. Si vous mettez du code en dehors des sections USER CODE , il sera supprimé chaque fois que le générateur de code s'exécutera (c'est-à-dire chaque fois que nous apporterons une modification à la configuration matérielle).

Pour l'instant, nous allons ajouter du code, comme ci-dessous. N'oubliez pas que vous pouvez obtenir des suggestions de saisie semi-automatique en appuyant sur Ctrl+Espace à tout moment.

![Image_2](https://01001000.xyz/assets/img/cubeide-timers/eclipse-autosuggest.png)

Ajoutez le code suivant :

Dans main.c, main():

```
/* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  HAL_Delay(1000);
  }
  /* USER CODE END 3 */
  ```
  
  Qu'est-ce que cela fait? J'espère que vous êtes capable de le résoudre ! 
  Dans la boucle infinie, il basculera d'abord la broche LED (en la changeant de haut en bas ou vice versa), puis il exécutera la HAL_Delay()fonction. 
  HAL_Delay est ce qu'on appelle une fonction de blocage . 
  À l'intérieur de la fonction se trouve une boucle qui itérera jusqu'à ce que le nombre de millisecondes que vous avez spécifié comme argument se soit écoulé. 
  En d'autres termes, il mettra l'exécution en pause. Dans notre cas, nous lui avons demandé de faire une pause de 1000 millisecondes. 
  Ainsi, lorsque nous compilons et téléchargeons cette fonction sur la carte, la LED clignote.
  
  ## Notre propre fonction de délais
  
  L'une des caractéristiques de la HAL_Delayfonction est qu'elle est basée sur le SysTick de votre microcontrôleur STM32. 
  Par défaut, il s'agit d'une interruption qui se déclenche toutes les millisecondes. 
  Cela ne nous donne pas une résolution énorme (par exemple, si nous voulions avoir un délai de 500 microsecondes, ce n'est pas possible par défaut).
  
  
  Maintenant, nous savons que l'architecture du microcontrôleur nous fournit une multitude de périphériques de minuterie à utiliser. 
  Voyons si nous pouvons utiliser l'un d'entre eux pour créer notre propre fonction de retard qui a une résolution plus élevée que celle par défaut HAL_Delay(). 
  Selon le ST General Purpose Timer Cookbook for STM32 Microcontrollers (une excellente ressource que vous pouvez consulter pour plus d'informations), la première minuterie, TIM1, a un schéma fonctionnel interne qui ressemble à ceci :
  
  ![Image_3](https://01001000.xyz/assets/img/cubeide-timers/timer-block-diagram.png)
  
  Il se passe pas mal de choses ici ! 
  Heureusement, nous voulons simplement utiliser l'un des modes les plus simples. 
  Examinons ce que nous voulons faire : 
  Tout d'abord, nous voulons compter le temps, pas les événements d'entrée, donc à partir de la boîte bleue, nous aurons la source de la minuterie basée sur les tics d'horloge du microcontrôleur. 
  Deuxièmement, nous devrons décider à quelle vitesse nous comptons en fonction de cette source d'horloge, c'est-à-dire devrions-nous compter les tics d'horloge directement, ou devrions-nous les diviser par une certaine valeur ? 
  Cette décision est représentée par la valeur du prescaler (représentée par le bloc PSC prescaler dans la case verte Time-base). 
  Enfin, le "compte" réel du temporisateur est stocké dans le registre CNT, avant que le matériel de prise de décision n'utilise cette valeur d'une autre manière (nous y reviendrons plus tard).
  
  Passons en revue un exemple. 
  Décidons que nous souhaitons que TIM1 compte en microsecondes . 
  Nous devons maintenant connaître la vitesse de l'horloge d'entrée TIM1. Dans l'outil de configuration de l'appareil, nous pouvons voir ce que c'est sous le panneau Configuration de l'horloge :
  
  ![Image_4](https://01001000.xyz/assets/img/cubeide-timers/clock-config.png)
  
  Ah ! Maintenant, alors que les deux vitesses sont les mêmes pour les horloges temporisées APB1 et les horloges temporisées APB2, si elles étaient différentes, comment saurions-nous de quelle source TIM1 dépendait ?

La fiche technique STM32F303RE peut nous sauver ici :

![Image_5](https://01001000.xyz/assets/img/cubeide-timers/cpu-timer-block.png)

Ainsi, TIM1 provient en fait de la source d'horloge de la minuterie APB2.

Maintenant que nous savons que dans notre configuration TIM1 a une source de 72 MHz, nous pouvons commencer à configurer l'appareil. 
Si nous voulons une résolution de 1 microseconde, nous savons que nous devrons diviser l'horloge par 72, car 72 MHz / 72 = 1 MHz, et 1 / 1 MHz = 1 microseconde. 
Il y a une autre note dont vous devez vous souvenir, à savoir que le pré-échelle est toujours stocké comme 1 de moins que la division. 
C'est-à-dire qu'un prescaler de 0 diviserait l'horloge par 1 (c'est-à-dire qu'il ne la diviserait pas). Pour notre division souhaitée, 72, nous devons donc régler le prescaler sur 71.

Retournez dans l'outil de configuration de l'appareil et développez les paramètres de TIM1 . Réglez Clock Source sur Internal Clock et Prescaler sur 71, comme illustré.

![Image_6](https://01001000.xyz/assets/img/cubeide-timers/tim1-config.png)

Maintenant, enregistrez votre configuration et appuyez sur Oui pour régénérer le code lorsque vous y êtes invité.

Vous devriez remarquer qu'une ligne supplémentaire de configuration est apparue dans votre main.c:

Dans main.c, main():
 ```
 /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
 ```
  
Super! Ajoutons maintenant notre propre petite fonction personnalisée :

Dans main.c la section code utilisateur privé :
```
 /* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_us (uint16_t us) //warning: this function is not reentrant
{
	__HAL_TIM_SET_COUNTER(&htim1,0); //reset the timer counter
	HAL_TIM_Base_Start(&htim1); //start the timer
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us value provided as an argument
	HAL_TIM_Base_Stop(&htim1); //stop the timer.
}
/* USER CODE END 0 */
``` 

Parcourons ce morceau de code. 
Nous prenons comme argument usle temps d'attente en microsecondes. 
Notez que notre argument est un type 16 bits. En effet, le registre CNT de TIM1 n'a qu'une largeur de 16 bits. Cela signifie qu'il ne peut compter que jusqu'à 2^16-1, ou 65535.

  La première ligne du corps de la fonction réinitialise le compteur au cœur de TIM1 en mettant le registre CNT (voir le schéma fonctionnel) à zéro. 
  La deuxième ligne démarre alors la minuterie. La troisième ligne attend que le registre CNT soit supérieur à l'argument que nous avons fourni. 
  Cela fonctionne car nous savons que le registre CNT avancera de 1 toutes les 1 microsecondes. Enfin, la quatrième ligne arrête le chronomètre.
  
  Il y a une chose à noter avec l'implémentation de cette fonction : elle n'est pas réentrante . 
  Qu'est-ce que ça veut dire? Étant donné que la fonction a des effets secondaires (elle réinitialise/démarre/arrête le minuteur) lorsqu'elle est appelée, si cette fonction devait être utilisée en parallèle, les deux appels de fonction interféreraient l'un avec l'autre. 
  Il est possible d'écrire une version de cette fonction telle qu'elle soit réentrante (comme HAL_Delay()), mais restons simples et ne nous en soucions pas pour l'instant.
  
  Essayons notre nouvelle fonctionnalité en modifiant notre while(1)in main.cpour utiliser la nouvelle fonction de délai. 
  Notez que, comme nous en avons discuté, nous ne pouvons pas demander un délai supérieur à 65 535 microsecondes. Je choisis d'utiliser 50 000 :

Dans main.c, main():

```
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		delay_us(50000);
  }
  ```
  
  Si nous compilons et exécutons ceci, nous devrions voir que la LED clignote maintenant beaucoup plus rapidement.
  
  ## Une interruption dans le timer
  
 Comment éviter d'avoir des fonctions bloquantes ? La réponse est de changer notre façon de penser. Plutôt que de vérifier en permanence si une requête est terminée (c'est-à-dire de vérifier si le délai s'est écoulé), nous devrions plutôt demander que l'architecture sous-jacente fasse le travail, puis nous informe lorsqu'elle est terminée. En termes informatiques, cela s'appelle une interruption .

Il existe de nombreuses façons de visualiser les interruptions, mais celle que j'aime le plus est de considérer un détecteur de fumée commun. Il fonctionne en parallèle avec vous à la maison, et si un incendie nécessite votre attention, il interrompra tout ce que vous faites en déclenchant l'alarme. Une fois que vous avez traité la cause du problème, vous pouvez retourner à votre vie de famille.

Dans le schéma synoptique du temporisateur, le matériel d'interruption est géré par les registres de capture/comparaison et représenté par les signaux CCxI. Ils ont quelques modes de fonctionnement différents, mais dans leur forme la plus simple, vous pouvez les considérer comme "une valeur à laquelle la minuterie compte".

Lorsque nous les configurons, nous pouvons les configurer de telle sorte que lorsque le temporisateur atteint une certaine valeur, il appelle une fonction dans notre programme C - que nous appelons Interrupt Service Routine , ou ISR .

Essayons un exemple. Faisons en sorte que notre minuterie déclenche une interruption toutes les 500 millisecondes. Retournez dans l'outil de configuration de l'appareil, puis revenez dans la configuration TIM1. Nous devrons changer notre Prescaler PSC de 71 (c'est-à-dire diviser l'horloge par 72) à 719 (c'est-à-dire diviser l'horloge par 720, chaque tick représentant 10 us). Ensuite, nous changerons la période du compteur en 49999 - ce qui signifie une période globale de 50 000 cycles (comme le pré-échelle, ce nombre est inférieur de 1 à la valeur exécutée).

![Image_7](https://01001000.xyz/assets/img/cubeide-timers/tim1-config2.png)

Nous devons maintenant activer le matériel d'interruption. Sélectionnez l'onglet Paramètres NVIC, puis cochez la case pour la mise à jour TIM1 (notez que cela partage une interruption TIM16, mais comme TIM16 n'est pas activé, cela ne nous dérange pas).

![Image_8](https://01001000.xyz/assets/img/cubeide-timers/tim1-enable-interrupt.png)

Nous devons maintenant ajouter du code pour utiliser cette interruption. Retournez à main.c. Écrivons d'abord l'ISR pour la période de temporisation écoulée :

Dans main.c, section code utilisateur privé :

```
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_us (uint16_t us) //warning: this function is not reentrant
{ . . . }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}
/* USER CODE END 0 */
```

Maintenant, nous devons réellement utiliser la minuterie (et supprimer le code LED clignotant du précédent).

Dans main.c, main():

```
/* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1); //start the timer
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // nothing to do in here at the moment . . .
  }
  /* USER CODE END 3 */
```

Notez que nous devons en fait démarrer nous-mêmes la minuterie en mode interruption, et n'oubliez pas de supprimer le code précédent de la section USER CODE 3.

Essayez l'exécution maintenant - qu'est-ce qui a changé ? Eh bien, la LED devrait maintenant clignoter de manière fiable avec une période de 1 seconde (c'est-à-dire 500 ms allumée, 500 ms éteinte).

Nous avons maintenant réussi à créer cette application pilotée par le temps en utilisant des interruptions. Cela signifie que nous pourrions mettre un autre code dans notre whileboucle principale et ne pas avoir à attendre tout le temps que les retards se terminent ! Dans les microcontrôleurs, les interruptions sont une étape clé sur le chemin des implémentations multitâches et des microcontrôleurs effectuant plusieurs tâches de contrôle à la fois.


## Introduction à la modulation de largeur d'impulsion (PWM)

Il s'avère que l'utilisation d'une minuterie pour allumer et éteindre une broche à intervalle régulier (c'est-à-dire sous forme d' onde carrée ) est une exigence de travail extrêmement courante. En effet, nous pouvons utiliser des signaux d'onde carrée avec des rapports cycliques variables (c'est-à-dire des rapports variables de temps d'activation et de désactivation) pour modifier la quantité effective de puissance transmise par un signal donné. C'est ce qu'on appelle la modulation de largeur d'impulsion , et Wikipédia a quelques beaux détails à ce sujet .

Nous pouvons distiller la partie importante dans cette image :

![Image_9](https://01001000.xyz/assets/img/cubeide-timers/dutycycle.png)

En faisant varier le rapport entre le temps haut et le temps bas tout en préservant la période du signal (et tout en préservant la tension et d'autres caractéristiques), nous sommes en mesure de modifier la quantité de puissance transmise.

Voyons un exemple. Nous allons devoir modifier à nouveau la configuration, alors revenez dans l'outil de configuration de l'appareil.

Nous allons piloter la LED intégrée à l'aide de PWM, nous devrons donc modifier la configuration de cette broche. Dans l'outil de configuration de l'appareil, réglez TIM1 pour qu'il ait à nouveau le zéro du prédiviseur et la période maximale (65535). Ensuite, définissez PA5 sur TIM2_CH1 , qui est une source PWM. Sélectionnez TIM2 sous Timers, activez-le en réglant Clock Source sur Internal Clock , puis réglez Channel 1 sur PWM Generation CH1 . Le choix de la période d'un signal PWM dépend largement de l'application que vous utilisez. Pour ce que nous allons faire, 1 kHz est une bonne valeur, nous allons donc régler à nouveau le prescaler sur 71 (ce qui nous donne une résolution de 1 microseconde) puis choisir une période de compteur de 999 (c'est-à-dire 1 000 microsecondes ou 1 milliseconde = 1 kHz) . Nous définirons ensuite un rapport cyclique initial de 50 % en réglant l'impulsion sur 499(moitié de 1 000 - 1).

Représenté :

![Image_10](https://01001000.xyz/assets/img/cubeide-timers/tim2-config.png)

Enregistrez et régénérez votre code. Maintenant, nous devons éditer à nouveau notre code. 
Tout d'abord, nous voulons utiliser l'interruption TIM1 pour modifier le rapport cyclique de TIM2. Cela nous permettra de visualiser les effets d'un rapport cyclique qui varie dans le temps.
Dans main.c, section code utilisateur privé :

```
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_us (uint16_t us) //warning: this function is not reentrant
{ . . . }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	//change the duty cycle of TIM2 whenever the TIM1 interrupt occurs.
	static uint8_t dir = 0; //direction: are we currently increasing duty cycle or currently decreasing?
	uint32_t i = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_1); //the period is 1000. Duty cycle should vary between 0 and 1000.

	if(dir == 0) { //change duty cycle by changing "i" by 1 in the positive or negative direction
		i--;
		if(i == 0) {
			dir = 1;
		}
	} else {
		i++;
		if(i == 1000) {
			dir = 0;
		}

	}
	//update the PWM control register
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, i);
}
/* USER CODE END 0 */
```

Il se passe beaucoup de choses là-dedans, mais j'espère que les commentaires pourront vous guider. Essentiellement, nous faisons varier le registre qui contrôle le rapport cyclique du signal PWM en le faisant passer de 0 (représentant 0% de rapport cyclique) à 1000 (représentant 100%). Comme cela a été codé comme TIM1 ISR, cela se produira chaque fois que TIM1 atteindra la fin de sa période.

Nous devons maintenant activer la sortie PWM.

Dans main.c, main():

```
/* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1); 
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //enable PWM output on LED pin
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // nothing to do in here at the moment . . .
  }
  /* USER CODE END 3 */
```

Comparez cela à plus tôt - cette LED s'allume et s'éteint maintenant lorsque le cycle de service PWM passe de 0% à 100%.


## PWM pour générer une transmission radio AM

Les signaux électriques tels que PWM ont tendance à émettre un rayonnement électromagnétique. Ce n'est généralement pas ce que nous voulons, mais pour le reste de ce tutoriel, nous allons en fait (ab)utiliser cette propriété pour générer une transmission radio AM !

Voyons d'abord brièvement ce qu'est la radio AM. AM signifie modulation d'amplitude. Cela signifie que nous prenons une onde porteuse et la combinons avec un signal d'information , en modifiant l' amplification de l'onde porteuse au fil du temps.

Comme toujours, Wikipedia a une excellente explication, et cette figure (CC BY-SA 3.0) d'Ivan Akira a une visualisation exceptionnelle de la façon dont la combinaison des signaux fonctionne dans la pratique :

![Image_11](https://01001000.xyz/assets/img/cubeide-timers/am-explain.png)


Pour une transmission audio AM, le signal d'information représente l'audio que nous voulons transmettre, et l'onde porteuse est la fréquence sur laquelle vous régleriez votre radio.

Grâce à une utilisation prudente des capacités PWM de notre microcontrôleur, nous pouvons générer un signal radio AM complet en utilisant uniquement un logiciel.

Remarque : Selon les lois de votre pays, la génération et l'émission de signaux d'ondes radio sans licence (même les signaux extrêmement faibles avec lesquels nous allons travailler ici) peuvent vous causer des ennuis. Procédez à vos risques et périls.

La première astuce consiste à générer l'onde porteuse elle-même, alors faisons-le maintenant. Je veux que ma fréquence soit à 1 000 kHz car c'est une fréquence assez normale pour la radio AM, et je devrai choisir une broche à utiliser comme antenne. J'ai sélectionné la broche étiquetée PWM/D9 sur les en-têtes Arduino. Si nous regardons le schéma de la carte, nous pouvons voir que cette broche va à PC7 sur le processeur, qui a la possibilité de devenir le canal PWM TIM3_CH2.

Faisons quelques calculs rapides. Si nous divisons l'horloge par 18, l'horloge est à 4 MHz. Si nous définissons ensuite la période d'horloge sur 4, nous obtenons une période globale de 1 MHz (ou 1 000 kHz). Pour obtenir une bonne onde porteuse, le rapport cyclique doit être de 50 %, nous avons donc réglé le Pulse sur 2.

![Image_12](https://01001000.xyz/assets/img/cubeide-timers/tim3-config.png)

Maintenant, activons le signal. Régénérez le code et reprenezmain.c :

Dans main.c, main():

```
/* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1); 
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //enable PWM output on LED pin
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // nothing to do in here at the moment . . .
  }
  /* USER CODE END 3 */
  ```
  Téléchargez-le maintenant sur votre carte et branchez un fil lâche dans la broche d'en-tête Arduino PWM/D9. Réglez une radio sur 1 kHz AM, puis appuyez sur le bouton de réinitialisation de votre carte. Vous devriez pouvoir entendre l'onde porteuse entrer et sortir.

Bien sûr, ce n'est pas extrêmement intéressant. Ce que nous aimerions faire, c'est superposer un signal audio au-dessus de cette onde. Devinez quoi - nous pouvons le faire (dans un sens). Rappelons que les ondes audio peuvent elles-mêmes être représentées de manière rectangulaire, et que AM dit que nous modifions l'amplification de notre signal.

Eh bien, bien que nous n'ayons pas de contrôle précis sur la tension de notre PWM, nous avons la possibilité de l'allumer et de l'éteindre, ce qui nous donne deux niveaux d'amplification - 0 % et 100 %. Donc, si notre signal audio est également composé uniquement d'ondes rectangulaires, nous pouvons les combiner, comme ceci :

![Image_13](https://01001000.xyz/assets/img/cubeide-timers/dutycycle-am-wave.png)

Alors, comment pouvons-nous générer ces ondes audio ? Eh bien, l'audio lui-même peut être représenté sous forme d'ondes carrées de fréquences variables . Par exemple, la note A4 est à 440 Hz, B4 à 493,88 Hz, etc.

Essayons de faire passer une seule tonalité par notre radio AM - A4. Cela signifie que nous devrons activer et désactiver le canal PWM 440 fois par seconde.

Pour ce faire, je vais réorganiser notre fonction delay_usde retard de la microseconde de plus tôt (car nous avons réaffecté TIM1 au travail de la LED de décoloration). Introduisons donc une autre minuterie, TIM4, et configurons-la avec un pré-échelle de 71, comme nous l'avons fait précédemment.

![Image_14](https://01001000.xyz/assets/img/cubeide-timers/tim4-config.png)

Régénérez votre code et mettez à jour la fonction delay_us pour l'utiliser maintenant à la htim4place de htim1. Nous allons également laisser la minuterie fonctionner en permanence, plutôt que de la démarrer et de l'arrêter (cela rendra la fonction légèrement plus précise car elle n'aura pas autant d'instructions superflues).

Dans main.c, section code utilisateur privé :
```
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_us (uint16_t us) //warning: this function is not reentrant. NOTE CHANGE TO TIMER 4
{
    __HAL_TIM_SET_COUNTER(&htim4,0); //reset the timer counter
	while (__HAL_TIM_GET_COUNTER(&htim4) < us);  // wait for the counter to reach the us value provided as an argument
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	. . .
}
/* USER CODE END 0 */
```


Et maintenant, mettez à jour notre principal pour activer et désactiver le PWM à une vitesse appropriée :

Dans main.c, main()
```
/* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //enable PWM output on LED pin
  HAL_TIM_Base_Start(&htim4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  delay_us(500000/440); //desired frequency is 440Hz, toggle at 220Hz. Delay is thus (1/f*1000000)/2 to get to us, or 500000/f.
	  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	  delay_us(500000/440);
	  HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_2);
  }
  /* USER CODE END 3 */
```

Si vous exécutez et téléchargez ceci maintenant, vous remarquerez qu'une tonalité à 440 Hz est générée par votre radio ! Si vous voulez un exercice pour vous-même, utilisez le bouton intégré pour allumer et éteindre le générateur de tonalité et vous avez maintenant un émetteur de code morse !

## Jouons de la musique :)

Étendre notre radio à une seule tonalité pour nous permettre de faire tourner une table de notes de musique (afin que nous puissions jouer une chanson) n'est pas particulièrement difficile à partir de ce point ! Passons en revue quelques modifications supplémentaires (rappelez-vous que cela delay_usest toujours basé sur TIM4).

Dans main.c, section code utilisateur privé :

```
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_us (uint16_t us) //warning: this function is not reentrant
{
    . . .
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	. . .
}

//First we define our note frequencies and delays via a conversion function, an enum, and our look-up-table array.
#define FREQ_TO_DELAY_US(x) (500000 / x)
typedef enum {
	note_a 		= 0,
	note_a_sh 	= 1,
	note_b 		= 2,
	note_c 		= 3,
	note_c_sh 	= 4,
	note_d 		= 5,
	note_d_sh 	= 6,
	note_e 		= 7,
	note_f 		= 8,
	note_f_sh 	= 9,
	note_g		= 10,
	note_g_sh	= 11
} note_enum;

#define SCALE_LEN 12
uint16_t note_delays_us[] = {
	FREQ_TO_DELAY_US(220),
	FREQ_TO_DELAY_US(233),
	FREQ_TO_DELAY_US(247),
	FREQ_TO_DELAY_US(262),
	FREQ_TO_DELAY_US(277),
	FREQ_TO_DELAY_US(294),
	FREQ_TO_DELAY_US(311),
	FREQ_TO_DELAY_US(330),
	FREQ_TO_DELAY_US(349),
	FREQ_TO_DELAY_US(370),
	FREQ_TO_DELAY_US(392),
	FREQ_TO_DELAY_US(415),
	FREQ_TO_DELAY_US(440),
	FREQ_TO_DELAY_US(466),
	FREQ_TO_DELAY_US(494),
	FREQ_TO_DELAY_US(523),
	FREQ_TO_DELAY_US(554),
	FREQ_TO_DELAY_US(587),
	FREQ_TO_DELAY_US(622),
	FREQ_TO_DELAY_US(659),
	FREQ_TO_DELAY_US(698),
	FREQ_TO_DELAY_US(740),
	FREQ_TO_DELAY_US(784),
	FREQ_TO_DELAY_US(831)
};

//Now we define note durations {Quarter, Eighth, Sixteenth, Thirtysecond; Half; Whole}
#define NOTE_LEN_Q 652
#define NOTE_LEN_E (NOTE_LEN_Q/2)
#define NOTE_LEN_S (NOTE_LEN_Q/4)
#define NOTE_LEN_T (NOTE_LEN_Q/8)
#define NOTE_LEN_H (NOTE_LEN_Q*2)
#define NOTE_LEN_W (NOTE_LEN_Q*4)

//playNote struct provides the container to hold a given note in a song together
typedef struct {
	note_enum note;         //the note that is played
	uint8_t scale_pos;      //is it our upper scale or our lower scale (either 0 or 1)
	uint16_t duration_ms;   //for how long will the note be played?
	uint16_t duration_rest; //after the note, how long should we rest for?
} playNote;

//A song made up as the struct
playNote furEliseSong[] = {
	{note_e, 1, NOTE_LEN_E, 0},
	{note_d_sh, 1, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_d_sh, 1, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_E, 0},
	{note_d, 1, NOTE_LEN_E, 0},
	{note_c, 1, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_c, 0, NOTE_LEN_E, 0},
	{note_e, 0, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_e, 0, NOTE_LEN_E, 0},
	{note_g_sh, 0, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_E, 0},
	{note_c, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_e, 0, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_d_sh, 1, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_d_sh, 1, NOTE_LEN_E, 0},
	{note_e, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_E, 0},
	{note_d, 1, NOTE_LEN_E, 0},
	{note_c, 1, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_c, 0, NOTE_LEN_E, 0},
	{note_e, 0, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_Q, NOTE_LEN_E},

	{note_e, 0, NOTE_LEN_E, 0},
	{note_c, 1, NOTE_LEN_E, 0},
	{note_b, 1, NOTE_LEN_E, 0},
	{note_a, 1, NOTE_LEN_Q, NOTE_LEN_Q}
};

//definitions finished, onto the functions to play the notes

//tx_tone takes a delay time and a play time, and will switch on and off the carrier PWM signal according to those arguments.
//this generates a tone in the PWM carrier in the AM frequency band.
void tx_tone(uint32_t dTime, uint32_t playTime) {
	uint32_t end = HAL_GetTick() + playTime;

  	while (end > HAL_GetTick()) {
	  	delay_us(dTime);
	  	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	  	delay_us(dTime);
	  	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
  	}
}

//tx_note takes a playNote structure and does the conversion into the arguments that tx_tone will take.
//firstly it transmits the note frequency (using the note_delay_us look up table) for 50 milliseconds less than requested,
//then it transmits "silence" for 50 milliseconds (this gives a gap between notes).
//Finally, if the playNote structure requests a further rest, it will extend the rest by that much amount of time.
void tx_note(playNote *n) {
	tx_tone(note_delays_us[n->note + SCALE_LEN * n->scale_pos], n->duration_ms-50);
	tx_tone(1, 50);
	if(n->duration_rest > 0) {
		tx_tone(1, n->duration_rest);
	}
}
/* USER CODE END 0 */
```

Il se passe beaucoup de choses ici, mais rassurez-vous, rien de tout cela n'est compliqué. Parlons brièvement de la théorie musicale.

Tout d'abord, comme nous l'avons vu précédemment, chaque note a une fréquence définie (c'est-à-dire que la note A est de 440 Hz). Nous avons montré dans l'exemple précédent comment nous utilisons la formule 500000/freq pour la convertir en un délai de basculement pour le code qui active et désactive rapidement le PWM (signal porteur) pour générer la note à cette tonalité. Ainsi, notre premier travail consiste à définir certaines notes et leurs fréquences. Je fais cela avec un #definequi contient la fonction pour convertir la fréquence en retard; a note_enumpour contenir les différents noms de note, et une table de recherche note_delaysqui contient des éléments correspondant aux valeurs de l'énumération. Comme je veux avoir deux gammes de notes, le note_delaystableau est deux fois plus long que le note_enumet je définis la longueur de la gamme à 12.

La théorie musicale dit aussi que les notes ont des durées , c'est-à-dire pendant combien de temps elles sont jouées. Ceux-ci sont tous en relation les uns avec les autres. Je définis la noire comme la note de base (car c'est la note la plus courante) à 652 millisecondes, ce qui signifie que nous jouons à environ 92 battements par minute.

Je définis ensuite une structure playNotecomme un conteneur pour contenir les notes de musique d'une chanson. Ils ont toutes les informations dont ils ont besoin regroupées : l'énumération de la note, la position de l'échelle et la durée. J'ajoute également un élément à la struct , qui peut être utilisé pour ajouter un silenceduration_rest musical une fois la note terminée.

On passe alors à deux fonctions. Le premier, tx_tone, fonctionne comme notre exemple précédent et active et désactive simplement le signal de porteuse PWM rapidement en fonction du retard de fréquence de note. La seconde, tx_note, prend un pointeur vers une playNotestructure et effectue la traduction dans le format/les arguments tx_tonerequis.

Et dans la boucle principale,

Dans main.c, main():
```
/* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //enable PWM output on LED pin
  HAL_TIM_Base_Start(&htim4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  for(int i = 0; i < 35; i++) { //35 notes to send
		  tx_note(&furEliseSong[i]);
	  }
  }
  /* USER CODE END 3 */
```
Ça y est, nous sommes prêts à partir. Compilez et lancez, et vous devriez entendre les premières mesures de Fur Elise via votre radio ! J'ai pris un enregistrement à l'aide de mon RTL-SDR pour démontrer :
Cela nous amène à la fin de ce tutoriel. N'hésitez pas à couper et à modifier le code fourni si nécessaire - voyez quelles autres fonctionnalités et/ou chansons vous pouvez produire !


