`timescale 1ns / 1ps

module circuit_1(input a, input b, input c, output out);

    wire w1, w2, nA;
    
    and #(5) (w1,a,b);
    not #(2) (nA,a);
    or #(9) (w2,nA,c);
    nand #(7) (w3,w2,w1);

    xor #(1) (out,w2,w3);
    
endmodule
