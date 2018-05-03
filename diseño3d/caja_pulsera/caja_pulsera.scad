use <write/write.scad>

difference(){
    //rectangulo ranura
    A=[10,5,1.5];
    //cubo principal
    cube([30,60,20]);
   
    //vaciado del cubo principal
    translate([2.5,1,2.5])
    cube([25,57.5,20]);
    //hueco cinta
    translate([10,0,3.5])
    cube(A);
    translate([10,0,6.5])
    cube(A);
    translate([10,57.5,3.5])
    cube(A);
    translate([10,57.5,6.5])
    cube(A);
    //hueco USB
    translate([12.5,0,15])
    cube([5,5,2.5]);
    //hueco switch
    translate([10,57.5,10])
    cube([10,10,5]);
    rotate([90,0,90])
    translate([12,7, 29.5])
    write("JUGGERBAND",t=3,h=5,center=false); 
    /*hueco carril
    translate([0,0,17.5])
    cube([1.5,59,2]);
    translate([28.5,0,17.5])
    cube([1.5,59,2]);*/
    
}
translate([2.5,57.5,20])
cube([25,2.5,4]);
//carril1b
difference(){
    translate([0,0,20])
    cube([2.5,60,4]);
    translate([1,0,20])
    cube([1.5,58.5,3]);
    
}   
//carril2b
difference(){
    translate([27.5,0,20])
    cube([2.5,60,4]);
    translate([27.5,0,20])
    cube([1.5,58.5,3]);
}
//tapa
translate([50,0,0]){
    difference(){       
        cube([26,57.5,2]);
        //hueco pantalla
        translate([5,2.5,0])
        cube([18,30,10]);     
         translate([10,50,1])
    write("Marcel",t=3,h=2,center=false); 
    }
    /*carril1
    translate([-2,0,-3.5])
    {
        cube([1,60,5.5]);
        translate([0,0,3.5])
        cube([2,60,2]);
        translate([1,0,0])
        cube([1.8,59,1.7]);
    }
    //carril2
    translate([31,0,-3.5]){
        cube([1,60,5.5]);
        translate([-2,0,3.5])
        cube([2,60,2]);
        translate([-1.8,0,0])
        cube([1.8,59,1.7]);
    }*/
    
   
}