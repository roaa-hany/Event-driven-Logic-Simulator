`timescale 1ns / 1ps

module circuit_3(input A,input B,input C,output out);

    wire w1;
    wire w2;

    and #(2) (w1,A,B);
    not #(1) (w2,C);
    xor #(3) (out,w1,w2);

endmodule
