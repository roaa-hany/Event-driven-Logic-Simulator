`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/14/2024 12:58:39 PM
// Design Name: 
// Module Name: circuit_4
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module circuit_4(

    );
    input A,B,C;
    output out;
    wire w1,w2,w3,w4,w5;
    not(w5,C);
    nand(w1, A,B);
    buf(w2,w1);
    and(w3,w1,w4);
    xnor(w4,B,w5);
    nor(out,w2,w3,w4);
endmodule
