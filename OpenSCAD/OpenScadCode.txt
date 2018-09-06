/*
   Arduino Project Source Code - OpenSCAD
   By: Sidak Pasricha
   Purpose: Allows a monitored growth for a plant. Basically, a Smart Plant Pot
   Application: Intended for maintaining a plant:
                The LED circuit switches on in case there is not enough light to prevent any harm to the plant growth.
                Accommodates for the circuit created using Arduino.
                
   Please note: Model is NOT TO SCALE with respect to real measurements: It is a pure mockup with proportions in mind.
*/
module pot(){
    /* Makes a Pot where the Plant is planted and monitored*/
    color("chocolate", 1)
    difference(){
        cylinder(h = 30, r1 = 10, r2 = 20, center = false);
        translate([0,0,2]){
            #cylinder(h = 28, r1 = 8, r2 = 18, center = false);
        }
    }
}
module arduino_box_half1(){
    /* Makes the first half of the Arduino Box */
    difference(){
        cube([15,10,2], center = false);
        translate([13,1,1]){
            #cube([4,3,2], center = false);
        }
        translate([2,-1,1]){
            #cube([11,12,2], center = false);
        }
    }
}
module arduino_box_half2(){
    /* Makes the second half of the Arduino Box */
    difference(){
        cube([15,10,2], center = false);
        translate([13,6,1]){
            #cube([4,3,2], center = false);
        }
        translate([2,-1,1]){
            #cube([11,12,2], center = false);
        }
    }
}
module arduino_box(){
    /* Combines the two halves into one and adds basic properties */
    color("chocolate", 1)
    translate([0, -5, 15])
    rotate([0,90,0]){
        arduino_box_half1();
        translate([0,10,4])
        rotate([180,0,0])
        arduino_box_half2();
    }
}


module breadboard(){
    /* Makes a breadboard cube which will contain the circuit */
    
    color("white", 1)
    rotate([0,0,90])
    cube([20,10,2], center = false);
    
    //Extra Light Source placed at the required location in the circuit, LEDs in ciruit are for demonstration only
    translate([-10,10,-2])
    sphere(3);
}
/* Creation of Modules */

pot();

translate([19,0,20])
arduino_box();

translate([20,-10,35])
breadboard();

