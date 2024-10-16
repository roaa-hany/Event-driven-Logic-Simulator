`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/14/2024 12:38:36 PM
// Design Name: 
// Module Name: circuit_1
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


module circuit_1();
    input a, b, c;
    output out;
    wire w1, w2, nA;
    
    and #(5) (w1, a, b, c);
    not #(2) (nA, a);
    or #(10) (w2, nA, c);
    nand #(7) (w3, w2, w1);

    xor(out, w2, w3);
    
endmodule
