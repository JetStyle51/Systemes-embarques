# Les debugguers

## La connection SWD

## La connection JTAG (Joint Test Action Group) : port d'accès de test

- TMS, (Test Mode Select) Signal d'activation de la communication JTAG,
- TCK, (Test ClocK) Horloge,
- TDI, (Test Data Input) Entrée des données,
- TDO, (Test Data Output) Sortie des données,
- TRST, (Test ReSeT) Réinitialisation. Ce signal optionnel est actif au niveau bas.

Il est à noter que certaines applications plus modernes sont dotées de signaux additionnels, tels que :

- RTCK, (Returned Test Clock) Signal optionnel permettant de dialoguer sur une fréquence automatiquement corrigée. Plutôt qu'un réglage manuel en Hz
- NRST, (Neutral Test Reset) Réinitialisation neutre matérielle. Signal commutant tout le matériel sur un statut connu du programmeur afin d'initier une communication plus facilement.