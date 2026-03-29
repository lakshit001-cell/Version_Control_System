import streamlit as st
from datetime import datetime

# --- 1. SETTINGS & STYLING ---
st.set_page_config(page_title="Time Travel FS", layout="wide")

# --- 2. INITIALIZE SESSION STATE (Your "HashMap" of Files) ---
if 'fs' not in st.session_state:
    st.session_state.fs = {}  # Keys: Filenames, Values: File Objects

# --- 3. HELPER FUNCTIONS ---
def create_file(name):
    if name and name not in st.session_state.fs:
        st.session_state.fs[name] = {
            "versions": [{"id": 0, "msg": "INITIAL SNAPSHOT", "content": "", "time": datetime.now()}],
            "active_idx": 0,
            "last_modified": datetime.now()
        }
        return True
    return False

def take_snapshot(name, content, msg):
    file = st.session_state.fs[name]
    new_version = {
        "id": len(file["versions"]),
        "msg": msg if msg else f"Update {len(file['versions'])}",
        "content": content,
        "time": datetime.now()
    }
    file["versions"].append(new_version)
    file["active_idx"] = new_version["id"]
    file["last_modified"] = datetime.now()

# --- 4. SIDEBAR: FILE MANAGEMENT ---
with st.sidebar:
    st.title("📁 File System")
    new_file_name = st.text_input("New Filename")
    if st.button("➕ Create File", use_container_width=True):
        if not create_file(new_file_name):
            st.error("File already exists or name invalid.")
        else:
            st.success(f"Created {new_file_name}")

    st.divider()
    
    # File Selection (The "HashMap" lookup)
    files_list = list(st.session_state.fs.keys())
    selected_file = st.selectbox("Select File", options=files_list) if files_list else None

    # Stats Section (Your "BIGGEST TREES" logic)
    if files_list:
        st.subheader(" Insights")
        biggest = sorted(st.session_state.fs.items(), key=lambda x: len(x[1]['versions']), reverse=True)[:3]
        for name, data in biggest:
            st.caption(f"{name}: {len(data['versions'])} snapshots")

# --- 5. MAIN AREA: EDITOR & TIME TRAVEL ---
if selected_file:
    file_data = st.session_state.fs[selected_file]
    active_ver = file_data["versions"][file_data["active_idx"]]

    col1, col2 = st.columns([3, 1])

    with col1:
        st.header(f" {selected_file}")
        st.caption(f"Currently viewing: **Version {active_ver['id']}** (Saved: {active_ver['time'].strftime('%H:%M:%S')})")
        
        # The Editor (UPDATE/INSERT logic)
        # We use a key based on the version ID so it resets when rolling back
        text_content = st.text_area(
            "File Content", 
            value=active_ver["content"], 
            height=400, 
            key=f"editor_{selected_file}_{file_data['active_idx']}"
        )

        # Snapshot Controls
        snap_msg = st.text_input("Snapshot Message", placeholder="What changed?")
        if st.button("📸 Take Snapshot", type="primary"):
            take_snapshot(selected_file, text_content, snap_msg)
            st.rerun()

    with col2:
        st.subheader("⏳ History")
        # Display versions in reverse (newest at top)
        for v in reversed(file_data["versions"]):
            with st.expander(f"V{v['id']} - {v['msg']}", expanded=(v['id'] == file_data['active_idx'])):
                st.write(f"**Time:** {v['time'].strftime('%H:%M:%S')}")
                if v['id'] != file_data['active_idx']:
                    if st.button(f"⏪ Rollback to V{v['id']}", key=f"rb_{v['id']}"):
                        file_data["active_idx"] = v['id']
                        st.rerun()
                else:
                    st.info("Active Version")
else:
    st.info("👈 Create or select a file from the sidebar to begin.")
