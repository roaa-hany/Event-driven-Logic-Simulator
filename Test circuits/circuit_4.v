`timescale 1ns / 1ps

module circuit_4(input A, input B, input C, output out);

    wire w1,w2,w3,w4,w5;

    not #(1) (w5,C);
    nand #(2) (w1, A,B);
    buf #(0) (w2,w1);
    and #(2) (w3,w1,w4);
    xnor #(3) (w4,B,w5);
    nor #(1) (out,w2,w3,w4);

endmodule
