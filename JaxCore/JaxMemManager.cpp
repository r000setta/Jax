#include "JaxMemManager.h"

Jax::JaxDebugMem::JaxDebugMem()
{
	m_uiNumNewCalls = 0;
	m_uiNumDeleteCalls = 0;
	m_uiNumBlocks = 0;
	m_uiNumBytes = 0;
	m_uiMaxNumBytes = 0;
	m_uiMaxNumBlocks = 0;
	m_pHead = NULL;
	m_pTail = NULL;

	for (size_t i = 0; i < RECORD_NUM; ++i)
	{
		m_uiSizeRecord[i] = 0;
	}
}

Jax::JaxDebugMem::~JaxDebugMem()
{
}

void* Jax::JaxDebugMem::Allocate(size_t size, size_t alignment, bool isArray)
{
	sm_MemLock.Lock();
	if (!size) {
		sm_MemLock.Unlock();
		return NULL;
	}
	m_uiNumNewCalls++;
	size_t extendedSize = sizeof(Block) + sizeof(size_t) + size + sizeof(size_t);
	char* pAddr = (char*)malloc(extendedSize);
	if (!pAddr) return NULL;
	Block* pBlock = (Block*)pAddr;
	pBlock->m_uiSize = size;
	pBlock->m_bIsArray = isArray;
	pBlock->m_bAlignment = (alignment > 0) ? true : false;
	pBlock->m_uiStackInfoNum = 0;
	InsertBlock(pBlock);
	pAddr += sizeof(Block);
	size_t* pBeginMask = (size_t*)(pAddr);
	*pBeginMask = BEGIN_MASK;
	pAddr += sizeof(size_t);
	size_t* pEndMask = (size_t*)(pAddr + size);
	*pEndMask = END_MASK;

	m_uiNumBlocks++;
	m_uiNumBytes += size;
	m_uiMaxNumBytes = max(m_uiMaxNumBytes, m_uiNumBytes);
	m_uiMaxNumBlocks = max(m_uiMaxNumBlocks, m_uiNumBlocks);
	sm_MemLock.Unlock();
	return (void*)pAddr;
}


