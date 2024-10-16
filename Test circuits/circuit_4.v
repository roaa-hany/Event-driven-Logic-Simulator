`timescale 1ns / 1ps

module circuit_4(input A, input B, input C, output o);

    wire w,y,z,x,t;

    not #(1) (t,C);
    nand #(2) (w,A,B);
    buf #(0) (y,w);
    and #(2) (z,y,x);
    xnor #(3) (x,B,t);
    nor #(1) (o,y,z);

endmodule
