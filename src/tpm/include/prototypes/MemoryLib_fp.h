/******************************************************************************************************************/
/*                                                                                                                */
/*                                                                                                                */
/*  Licenses and Notices                                                                                          */
/*                                                                                                                */
/*  1.  Copyright Licenses:                                                                                       */
/*     Trusted Computing Group (TCG) grants to the user of the source code in this specification (the             */
/*     "Source Code") a worldwide, irrevocable, nonexclusive, royalty free, copyright license to                  */
/*     reproduce, create derivative works, distribute, display and perform the Source Code and                    */
/*     derivative works thereof, and to grant others the rights granted herein.                                   */
/*     The TCG grants to the user of the other parts of the specification (other than the Source Code)            */
/*     the rights to reproduce, distribute, display, and perform the specification solely for the purpose         */
/*     of developing products based on such documents.                                                            */
/*                                                                                                                */
/*  2.  Source Code Distribution Conditions:                                                                      */
/*     Redistributions of Source Code must retain the above copyright licenses, this list of conditions           */
/*     and the following disclaimers.                                                                             */
/*     Redistributions in binary form must reproduce the above copyright licenses, this list of                   */
/*     conditions and the following disclaimers in the documentation and/or other materials provided              */
/*     with the distribution.                                                                                     */
/*                                                                                                                */
/*  3.  Disclaimers:                                                                                              */
/*     THE COPYRIGHT LICENSES SET FORTH ABOVE DO NOT REPRESENT ANY FORM OF LICENSE OR                             */
/*     WAIVER, EXPRESS OR IMPLIED, BY ESTOPPEL OR OTHERWISE, WITH RESPECT TO PATENT RIGHTS                        */
/*     HELD BY TCG MEMBERS (OR OTHER THIRD PARTIES) THAT MAY BE NECESSARY TO IMPLEMENT                            */
/*     THIS SPECIFICATION OR OTHERWISE. Contact TCG Administration                                                */
/*     (admin@trustedcomputinggroup.org) for information on specification licensing rights available              */
/*     through TCG membership agreements.                                                                         */
/*     THIS SPECIFICATION IS PROVIDED "AS IS" WITH NO EXPRESS OR IMPLIED WARRANTIES                               */
/*     WHATSOEVER, INCLUDING ANY WARRANTY OF MERCHANTABILITY OR FITNESS FOR A                                     */
/*     PARTICULAR PURPOSE, ACCURACY, COMPLETENESS, OR NONINFRINGEMENT OF INTELLECTUAL                             */
/*     PROPERTY RIGHTS, OR ANY WARRANTY OTHERWISE ARISING OUT OF ANY PROPOSAL,                                    */
/*     SPECIFICATION OR SAMPLE.                                                                                   */
/*     Without limitation, TCG and its members and licensors disclaim all liability, including liability for      */
/*     infringement of any proprietary rights, relating to use of information in this specification and to        */
/*     the implementation of this specification, and TCG disclaims all liability for cost of procurement          */
/*     of substitute goods or services, lost profits, loss of use, loss of data or any incidental,                */
/*     consequential, direct, indirect, or special damages, whether under contract, tort, warranty or             */
/*     otherwise, arising in any way out of use or reliance upon this specification or any information            */
/*     herein.                                                                                                    */
/*     Any marks and brands contained herein are the property of their respective owner.                          */
/*                                                                                                                */
/******************************************************************************************************************/

#ifndef _MEMORYLIB_FP_H_
#define _MEMORYLIB_FP_H_

LIB_EXPORT void
MemoryMove(
    void *destination,           // OUT: move destination
    const void *source,                // IN: move source
    UINT32 size,               // IN: number of octets to moved
    UINT32 dSize               // IN: size of the receive buffer
);

#define MemoryCopy(destination, source, size, destSize) \
 MemoryMove((destination), (source), (size), (destSize))
LIB_EXPORT BOOL
MemoryEqual(
    const void *buffer1,              // IN: compare buffer1
    const void *buffer2,              // IN: compare buffer2
    UINT32 size                   // IN: size of bytes being compared
);

LIB_EXPORT INT16
MemoryCopy2B(
    TPM2B *dest,              // OUT: receiving TPM2B
    const TPM2B *source,            // IN: source TPM2B
    UINT16 dSize               // IN: size of the receiving buffer
);

LIB_EXPORT void
MemoryConcat2B(
    TPM2B *aInOut,            // IN/OUT: destination 2B
    TPM2B *bIn,               // IN: second 2B
    UINT16 aSize               // IN: The size of aInOut.buffer (max values for
    // aInOut.size)
);

LIB_EXPORT BOOL
Memory2BEqual(
    const TPM2B *aIn,               // IN: compare value
    const TPM2B *bIn                // IN: compare value
);

LIB_EXPORT void
MemorySet(
    void *destination,             // OUT: memory destination
    char value,                  // IN: fill value
    UINT32 size                    // IN: number of octets to fill
);

BYTE *
MemoryGetActionInputBuffer(
    UINT32 size                    // Size, in bytes, required for the input
    // unmarshaling
);

void *
MemoryGetActionOutputBuffer(
    TPM_CC command            // Command that requires the buffer
);

BYTE *
MemoryGetResponseBuffer(
    TPM_CC command            // Command that requires the buffer
);

UINT16
MemoryRemoveTrailingZeros (
    TPM2B_AUTH *auth              // IN/OUT: value to adjust
);

#endif  // _MEMORYLIB_FP_H_
