`timescale 1ns / 1ps

module Circuit1(input A, input B, input C,output F);

wire W1;
and #(2) First(W1,A,B);
or #(1) Second(F,W1,C);

endmodule
