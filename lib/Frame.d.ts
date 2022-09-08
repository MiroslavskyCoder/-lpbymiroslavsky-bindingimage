/// <reference types="node" />
export declare type IPixel = Array<number>;
export interface IFrame {
    getWidth(): number;
    getHeight(): number;
    getPixel(x: number, y: number): IPixel;
    toBuffer(ext: string): Buffer;
}
export interface IFrameConstructor {
    readonly prototype: IFrame;
    new (path: string): IFrame;
}
export declare const IFrame: IFrameConstructor;
