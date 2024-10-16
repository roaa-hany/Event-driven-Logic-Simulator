`timescale 1ns / 1ps

module circuit_3(input A,input B,input C,output o);

    wire w;
    wire y;

    and #(2) (w,A,B);
    not #(1) (y,C);
    xor #(3) (o,w,y);

endmodule
