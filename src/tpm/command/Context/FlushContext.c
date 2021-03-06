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
/*     the rights to reproduce, distribute, display, and perform the specification solely for the purpose of      */
/*     developing products based on such documents.                                                               */
/*                                                                                                                */
/*  2.  Source Code Distribution Conditions:                                                                      */
/*     Redistributions of Source Code must retain the above copyright licenses, this list of conditions           */
/*     and the following disclaimers.                                                                             */
/*     Redistributions in binary form must reproduce the above copyright licenses, this list of conditions        */
/*     and the following disclaimers in the documentation and/or other materials provided with the                */
/*     distribution.                                                                                              */
/*                                                                                                                */
/*  3.  Disclaimers:                                                                                              */
/*     THE COPYRIGHT LICENSES SET FORTH ABOVE DO NOT REPRESENT ANY FORM OF                                        */
/*     LICENSE OR WAIVER, EXPRESS OR IMPLIED, BY ESTOPPEL OR OTHERWISE, WITH                                      */
/*     RESPECT TO PATENT RIGHTS HELD BY TCG MEMBERS (OR OTHER THIRD PARTIES)                                      */
/*     THAT MAY BE NECESSARY TO IMPLEMENT THIS SPECIFICATION OR OTHERWISE.                                        */
/*     Contact TCG Administration (admin@trustedcomputinggroup.org) for information on specification              */
/*     licensing rights available through TCG membership agreements.                                              */
/*     THIS SPECIFICATION IS PROVIDED "AS IS" WITH NO EXPRESS OR IMPLIED WARRANTIES                               */
/*     WHATSOEVER, INCLUDING ANY WARRANTY OF MERCHANTABILITY OR FITNESS FOR A                                     */
/*     PARTICULAR PURPOSE, ACCURACY, COMPLETENESS, OR NONINFRINGEMENT OF                                          */
/*     INTELLECTUAL PROPERTY RIGHTS, OR ANY WARRANTY OTHERWISE ARISING OUT OF                                     */
/*     ANY PROPOSAL, SPECIFICATION OR SAMPLE.                                                                     */
/*     Without limitation, TCG and its members and licensors disclaim all liability, including liability for      */
/*     infringement of any proprietary rights, relating to use of information in this specification and to the    */
/*     implementation of this specification, and TCG disclaims all liability for cost of procurement of           */
/*     substitute goods or services, lost profits, loss of use, loss of data or any incidental, consequential,    */
/*     direct, indirect, or special damages, whether under contract, tort, warranty or otherwise, arising in      */
/*     any way out of use or reliance upon this specification or any information herein.                          */
/*     Any marks and brands contained herein are the property of their respective owner.                          */
/*                                                                                                                */
/******************************************************************************************************************/

#include "InternalRoutines.h"
#include "FlushContext_fp.h"
#ifdef TPM_CC_FlushContext             // Conditional expansion of this file

// M e
// TPM_RC_HANDLE flushHandle does not reference a loaded object or session

TPM_RC
TPM2_FlushContext(
    FlushContext_In *in                      // IN: input parameter list
)
{
// Internal Data Update

    // Call object or session specific routine to flush
    switch(HandleGetType(in->flushHandle))
    {
    case TPM_HT_TRANSIENT:
        if(!ObjectIsPresent(in->flushHandle))
            return TPM_RC_HANDLE;
        // Flush object
        ObjectFlush(in->flushHandle);
        break;
    case TPM_HT_HMAC_SESSION:
    case TPM_HT_POLICY_SESSION:
        if( !SessionIsLoaded(in->flushHandle)
                && !SessionIsSaved(in->flushHandle)
          )
            return TPM_RC_HANDLE;

        // If the session to be flushed is the exclusive audit session, then
        // indicate that there is no exclusive audit session any longer.
        if(in->flushHandle == g_exclusiveAuditSession)
            g_exclusiveAuditSession = TPM_RH_UNASSIGNED;

        // Flush session
        SessionFlush(in->flushHandle);
        break;
    default:
        // This command only take object or session handle. Other handles
        // should be filtered out at handle unmarshal
        pAssert(FALSE);
        break;
    }

    return TPM_RC_SUCCESS;
}
#endif // CC_FlushContext
