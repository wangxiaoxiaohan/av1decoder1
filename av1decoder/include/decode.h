class decode{
    decode();
    ~decode();
	static decode& Instance() {
		static decode m_pInstance;
		return m_pInstance;
	}
};