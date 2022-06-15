ΟΜΑΔΑ: LAB MAGICIANS

Μαθήτρια : Κατερίνα Χαιρετάκη

Καθηγητές: συντονιστής -->Νεκτάριος Κουράκης (Φυσικός) και συνεργάτες-->(α)*Γιώργος Μαυροματάκης(Βιολόγος) και (β)**Μάνια Γαρεδάκη(Χημικός)


ΤΙΤΛΟΣ:LAB ECO ή eco Lab

ΣΥΣΚΕΥΗ ΠΟΛΛΑΠΛΩΝ ΧΡΗΣΕΩΝ ΣΤΟ ΕΡΓΑΣΤΗΡΙΟ ΘΕΤΙΚΩΝ ΕΠΙΣΤΗΜΩΝ

Με την πλατφόρμα – μικροελεγκτή  arduino με τους κατάλληλους αισθητήρες όπως και ένα rasberry(*LAB MODE**) φτιάξαμε μια συσκευή που χρησιμεύει σε πολλαπλά σενάρια  σχολικής χρήσης . Μια από τις χρήσεις του είναι η μέτρηση του CO2 α)*στην διαδικασία της φωτοσύνθεσης - σε συνδυασμό με αισθητήρα φωτός (σε lux) για την μελέτη του φαινομένου β)**σε χημικές αντιδράσεις (μάθημα χημείας) γ)στις σχολικές αίθουσες , στοιχείο που υποδεικνύει την ανάγκη καλύτερου εξαερισμού  όταν το CO2 ξεπερνάει το όριο ,προστατεύοντας έτσι από ασθένειες που αναπτύσσονται σε επιβαρυμένα περιβάλλοντα. Επίσης χρησιμοποιούμε lux (φωτεινότητας) αισθητήρα ,θερμοκρασίας ,υγρασίας και πίεσης. Έτσι όταν στην σχολική αίθουσα το επίπεδο φωτεινότητας πέφτει κάτω από το αναγκαίο για την ανάγνωση και γραφή , θα μας προειδοποιεί ώστε να αυξάνουμε το φως όπως και για τις κατάλληλες συνθήκες μαθήματος.

Έτσι φτιάξαμε μια κυκλικά χρησιμοποιήσιμη συσκευή πολλαπλών χρήσεων που προσαρμόζεται στις ανάγκες μας .Επίσης αναβαθμίζει το σχολικό εργαστήριο με μια συσκευή πολλαπλής χρήσης .

Σημαντικό στοιχείο αυτής της κατασκευής θα είναι η επεκτασιμότητά της μέσω της διασποράς των στοιχείων κατασκευής της σε ιστοσελίδα του ΕΚΦΕ ΧΑΝΙΩΝ-ΕΛΛΑΚ-GITHUB ώστε συνάδελφοι των φυσικών επιστημών ή πληροφορικής να προτείνουν προσθήκες ,επεκτάσεις και αλλαγές.  Ο σκοπός είναι να λάβουν και να μεταδώσουν τεχνογνωσία "ανήσυχοι" συνάδελφοι ώστε να υποστεί αυτή η συσκευή μια παραγωγική εξέλιξη.

SOFTWARE

1)    ARDUINO IDE

2)    Raspberry Pi OS (Raspbian) 

Κύκλωμα:

α) κύριο κύκλωμα link   https://github.com/nektarios25ma/LAB-ECO-MULTIPLE-USE/blob/main/circuit_all.png 

β)LAB MODE-->για το εργαστήριο επιπρόσθετο στοιχείο κυκλώματος link:https://github.com/nektarios25ma/LAB-ECO-MULTIPLE-USE/blob/main/RELAYfunCONNECTION.png

γ)Διακόπτης-switch με 3 pin για την επιλογή χρήσης LAB MODE (1) OR CLASS MODE (0) circuit link: https://github.com/nektarios25ma/LAB-ECO-MULTIPLE-USE/blob/main/RELAYfunCONNECTION.png

Πρόγραμμα-sketch arduino,link: https://github.com/nektarios25ma/LAB-ECO-MULTIPLE-USE/blob/main/TESTSWITCHSENARIO3.ino

ΥΛΙΚΑ

1)ΑΙΣΘΗΤΗΡΑΣ CO2

https://grobotronics.com/infrared-co2-sensor-0-5000-ppm-mh-z19b.html

€42.00

2) Αισθητήρας Φωτός

https://grobotronics.com/adafruit-tsl2591-high-dynamic-range-digital-light-sensor.html

€8.80

3)    ΑΙΣΘΗΤΗΡΑΣ θερμοκρασίας –υγρασίας-πίεσης

https://grobotronics.com/waveshare-temperature-humidity-sensor-dht22.html

€10.90

4) arduino uno

https://grobotronics.com/funduino-uno-rev3-arduino-uno-compatible.html

€11.90

5) Οθόνη lcd i2c 16x2

https://grobotronics.com/basic-16x2-character-lcd-white-on-blue-5v-i2c-protocol.html

€5.90

6)διακόπτης: €0.50

https://grobotronics.com/rocker-switch-on-off-blackdaier.html

7) Πλακέτα Δοκιμών Mini

https://grobotronics.com/breadboard-mini-white.html

€1.60

8)step down voltage : €4.60

https://grobotronics.com/ubec-dc-dc-step-down-buck-converter-5v-3a-output-el.html

9)κουτί μπαταρίας

https://grobotronics.com/battery-holder-2x18650-with-wires-and-switchoem.html

€1.20

10)2 x 18650 μπαταρίες: https://grobotronics.com/ncr18650b-3350mah-panasonic.html

2X €9.90

11) Προαιρετικά rasberry pi  3 για το (α) σενάριο: link https://grobotronics.com/raspberry-pi-3-model-b-el.html

€44.90

GITHUB: https://github.com/nektarios25ma/LAB-ECO-MULTIPLE-USE/blob/main/README.md

(α) Στην διαδικασία της φωτοσύνθεσης:

Θα χρειαστούμε ένα rasberry 3 ή 4 το οποίο θα λαμβάνει ενσύρματα δεδομένα από το arduino {video-link*tutorial -σωστή εγκατάσταση arduino ide στο rasberry} και θα τα προβάλει σε μια οθόνη ως γραφική παράσταση 4 δεδομένων: 

1. CO2 σε ppm  2.φωτός σε lux  3.θερμοκρασίας σε Celsious  4.υγρασίας % για την μελέτη του φαινομένου της φωτοσύνθεσης σε μικρό-μίνι θερμοκήπιο μέσα στο εργαστήριο.


Επίσης μπορούμε από οποιοδήποτε σημείο του κόσμου  να ελέγξουμε το rasberry  και κατ'επέκταση το arduino όπως και να δο΄ύμε την γραφική παράσταση των δεδομένων: CO2 ppm, lux (light), humidity%, temp(Celcius).
Ο τρόπος που γίνεται εδώ : https://www.youtube.com/watch?v=OE2FC1aSAqM και εδώ : https://www.circuitbasics.com/access-raspberry-pi-desktop-remote-connection/

Μια πρώτη δοκιμή δείτε στο : video link 
https://drive.google.com/file/d/1J-bW9p7WnPqtOV24Ilc-qzYuz5E1nNtc/view?usp=sharing

 στο you tube με υπότιτλους : https://youtube.com/shorts/p183HJfYlis


