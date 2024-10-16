`timescale 1ns / 1ps

module circuit_1(input a, input b, input c, output o);

    wire w, y, n, z;
    
    and #(5) (w,a,b);
    not #(2) (n,a);
    or #(9) (y,n,c);
    nand #(7) (z,y,w);

    xor #(1) (o,y,z);
    
endmodule
