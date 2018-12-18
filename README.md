<p align="center"><video autoplay controls loop muted src="/Media/VID_whitout_sound.mp4"></video></p>

<p align="justify">Aujourd’hui, nous réalisons un compteur de likes Facebook, Instagram et Twitter connecté en wifi. Il vous permettra d’afficher votre nombre de likes depuis votre page facebook, ainsi que votre nombre de followers instagram et twitter.</p>

### Liste de matériel :bookmark_tabs:
***
Afin de réaliser votre compteur de likes, il vous faudra :

| Quantité |            Composant            |
|:--------:|:-------------------------------:|
|     1    | LinkNode D1     		         |
|     1    | Matrice LED 32x8 (HT1632) 		 |
|     5    | fils connecteur Mâle-Femelle    |

### Montage :wrench:
***
Connectez les 5 fils de la manière suivante :

| Matrice LED |         LinkNode D1          |
|:-----------:|:----------------------------:|
|     5v      | 5v		     		         |
|     GND     | GND					 		 |
|     CS1     | D2						     |
|     WR      | D3					 		 |
|     DATA    | D4						     |

<p align="center"> <img src="/Media/like_counter_wire.png" alt="like counter wire"></p>
<p align="justify">Si vous disposez d’une imprimante 3D, vous pouvez télécharger le fichier d’impression 3D afin de fabriquer le boîtier. Visser l’écran ainsi que le LinkNode D1 de la manière suivante :</p>
<p align="center"> <img src="/Media/IMG_20181217.jpg" alt="like counter wire"></p>

### Le code :computer:
***

