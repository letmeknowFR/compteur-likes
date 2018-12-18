<p align="center"><img src="/Media/screen_capture.png" alt="like counter"></p>

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
<ol><li>Téléchargez la dernière version de l'<a href="https://www.arduino.cc/en/Main/Software">IDE Arduino.</a></li>
	<li>Si vous utilisez le LinkNode D1, vous allez devoir ajouter la carte dans la liste des cartes prises en charge par l'IDE Arduino. Ouvrez l'IDE, "Fichier" → "Préférences" et dans "URL de gestionnaire de cartes supplémentaires" ajouter le lien suivant :<blockquote class="wp-block-quote"><p><br><strong>http://arduino.esp8266.com/stable/package_esp8266com_index.json</strong></p></blockquote></li>
	<li>Vous&nbsp;pouvez télécharger le code du compteur de likes sur <a href="https://github.com/letmeknowFR/compteur-likes">github</a>.</li>
	<li>Déplacer les librairies téléchargées avec le compteur de likes dans votre répertoire Arduino <strong><em>/librairies</em></strong></li><figure class="wp-block-image"><img src="/Media/Diagram.png" alt="" class="wp-image-1869"><figcaption>Votre répertoire Arduino devrait ressembler à cela</figcaption></figure>
	<li>Raccordez votre compteur de likes grâce à un câble USB/microUSB&nbsp; vers votre ordinateur.</li>
	<li>Ouvrez votre IDE Arduino et modifiez les lignes <strong>23-24</strong> par le nom de votre réseau wifi ainsi que le mot de passe.</li><figure class="wp-block-image"><img src="/Media/CaptureWifi.PNG" alt="" class="wp-image-1875"/></figure></ol>