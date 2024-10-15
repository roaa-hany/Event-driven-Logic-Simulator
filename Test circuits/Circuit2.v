`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/14/2024 12:47:08 PM
// Design Name: 
// Module Name: Circuit2
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


module Circuit2(inptu A1,input B1,input C1,output F1);
wire NOT1;
wire NOT2;
wire NOT3;
wire AND1;
not not1(NOT1,A1);
not not2(NOT2,B1);
and and1(AND1,NOT1,NOT2);
not not3(NOT3,AND1);
or or1(F,not3,C1);
endmodule
