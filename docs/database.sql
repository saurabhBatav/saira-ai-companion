--
-- PostgreSQL database dump
--

-- Dumped from database version 16.3 (PGlite 0.2.0)
-- Dumped by pg_dump version 16.4

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'SQL_ASCII';
SET standard_conforming_strings = off;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET escape_string_warning = off;
SET row_security = off;

--
-- Name: meta; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA meta;


ALTER SCHEMA meta OWNER TO postgres;

--
-- Name: vector; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS vector WITH SCHEMA public;


--
-- Name: EXTENSION vector; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION vector IS 'vector data type and ivfflat and hnsw access methods';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: embeddings; Type: TABLE; Schema: meta; Owner: postgres
--

CREATE TABLE meta.embeddings (
    id bigint NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    content text NOT NULL,
    embedding public.vector(384) NOT NULL
);


ALTER TABLE meta.embeddings OWNER TO postgres;

--
-- Name: embeddings_id_seq; Type: SEQUENCE; Schema: meta; Owner: postgres
--

ALTER TABLE meta.embeddings ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME meta.embeddings_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: migrations; Type: TABLE; Schema: meta; Owner: postgres
--

CREATE TABLE meta.migrations (
    version text NOT NULL,
    name text,
    applied_at timestamp with time zone DEFAULT now() NOT NULL
);


ALTER TABLE meta.migrations OWNER TO postgres;

--
-- Name: conversations; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.conversations (
    id text NOT NULL,
    user_id text NOT NULL,
    start_time timestamp without time zone NOT NULL,
    end_time timestamp without time zone,
    title text,
    personality_profile_id text,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.conversations OWNER TO postgres;

--
-- Name: goals; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.goals (
    id text NOT NULL,
    user_id text NOT NULL,
    title text NOT NULL,
    description text,
    status text NOT NULL,
    due_date timestamp without time zone,
    progress real DEFAULT 0.0,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.goals OWNER TO postgres;

--
-- Name: journal_entries; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.journal_entries (
    id text NOT NULL,
    user_id text NOT NULL,
    "timestamp" timestamp without time zone NOT NULL,
    content text NOT NULL,
    detected_emotions text,
    associated_memories text,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.journal_entries OWNER TO postgres;

--
-- Name: memories; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.memories (
    id text NOT NULL,
    user_id text NOT NULL,
    type text NOT NULL,
    content text NOT NULL,
    embedding bytea NOT NULL,
    source_id text,
    source_type text,
    "timestamp" timestamp without time zone NOT NULL,
    relevance_score real DEFAULT 0.0,
    is_active boolean DEFAULT true,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.memories OWNER TO postgres;

--
-- Name: messages; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.messages (
    id text NOT NULL,
    conversation_id text NOT NULL,
    sender_type text NOT NULL,
    content text NOT NULL,
    "timestamp" timestamp without time zone NOT NULL,
    audio_path text,
    emotion_arousal real,
    emotion_valence real,
    emotion_category text,
    is_proactive_nudge boolean DEFAULT false,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.messages OWNER TO postgres;

--
-- Name: mood_summaries; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.mood_summaries (
    id text NOT NULL,
    user_id text NOT NULL,
    date date NOT NULL,
    summary_text text,
    aggregated_emotions text,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.mood_summaries OWNER TO postgres;

--
-- Name: nudge_history; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.nudge_history (
    id text NOT NULL,
    user_id text NOT NULL,
    nudge_preference_id text NOT NULL,
    "timestamp" timestamp without time zone NOT NULL,
    message_content text NOT NULL,
    delivered boolean DEFAULT true,
    interacted boolean DEFAULT false,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.nudge_history OWNER TO postgres;

--
-- Name: nudge_preferences; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.nudge_preferences (
    id text NOT NULL,
    user_id text NOT NULL,
    type text NOT NULL,
    frequency text NOT NULL,
    time_of_day text,
    content_template text NOT NULL,
    enabled boolean DEFAULT true,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.nudge_preferences OWNER TO postgres;

--
-- Name: personality_profiles; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.personality_profiles (
    id text NOT NULL,
    user_id text,
    name text NOT NULL,
    description text,
    llm_prompt_template text NOT NULL,
    tone_preferences text,
    memory_visibility_rules text,
    is_custom boolean DEFAULT false,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);


ALTER TABLE public.personality_profiles OWNER TO postgres;

--
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id text NOT NULL,
    name text NOT NULL,
    onboarding_completed boolean DEFAULT false,
    current_personality_profile_id text,
    last_active_at timestamp without time zone,
    created_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    sync_enabled boolean DEFAULT false,
    last_synced_at timestamp without time zone,
    sync_frequency text DEFAULT 'manual'::text,
    encryption_key_hash text NOT NULL,
    privacy_consent_version text NOT NULL,
    gdpr_ccpa_consent boolean NOT NULL,
    audit_logging_enabled boolean DEFAULT true,
    data_portability_token text,
    data_deletion_requested_at timestamp without time zone,
    profile_image_path text,
    preferred_tone_style text DEFAULT 'empathetic'::text,
    wake_word_enabled boolean DEFAULT true,
    proactive_nudges_enabled boolean DEFAULT true,
    deep_talk_mode_enabled boolean DEFAULT true,
    emotion_recording_consent boolean NOT NULL,
    memory_recording_consent boolean NOT NULL,
    journaling_enabled boolean DEFAULT true
);


ALTER TABLE public.users OWNER TO postgres;

--
-- Data for Name: embeddings; Type: TABLE DATA; Schema: meta; Owner: postgres
--



--
-- Data for Name: migrations; Type: TABLE DATA; Schema: meta; Owner: postgres
--

INSERT INTO meta.migrations VALUES ('202407160001', 'embeddings', '2025-06-14 15:23:31.893+00');


--
-- Data for Name: conversations; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: goals; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: journal_entries; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: memories; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: messages; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: mood_summaries; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: nudge_history; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: nudge_preferences; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: personality_profiles; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--



--
-- Name: embeddings_id_seq; Type: SEQUENCE SET; Schema: meta; Owner: postgres
--

SELECT pg_catalog.setval('meta.embeddings_id_seq', 1, false);


--
-- Name: embeddings embeddings_pkey; Type: CONSTRAINT; Schema: meta; Owner: postgres
--

ALTER TABLE ONLY meta.embeddings
    ADD CONSTRAINT embeddings_pkey PRIMARY KEY (id);


--
-- Name: migrations migrations_pkey; Type: CONSTRAINT; Schema: meta; Owner: postgres
--

ALTER TABLE ONLY meta.migrations
    ADD CONSTRAINT migrations_pkey PRIMARY KEY (version);


--
-- Name: conversations conversations_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.conversations
    ADD CONSTRAINT conversations_pkey PRIMARY KEY (id);


--
-- Name: goals goals_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.goals
    ADD CONSTRAINT goals_pkey PRIMARY KEY (id);


--
-- Name: journal_entries journal_entries_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.journal_entries
    ADD CONSTRAINT journal_entries_pkey PRIMARY KEY (id);


--
-- Name: memories memories_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.memories
    ADD CONSTRAINT memories_pkey PRIMARY KEY (id);


--
-- Name: messages messages_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_pkey PRIMARY KEY (id);


--
-- Name: mood_summaries mood_summaries_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.mood_summaries
    ADD CONSTRAINT mood_summaries_pkey PRIMARY KEY (id);


--
-- Name: nudge_history nudge_history_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.nudge_history
    ADD CONSTRAINT nudge_history_pkey PRIMARY KEY (id);


--
-- Name: nudge_preferences nudge_preferences_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.nudge_preferences
    ADD CONSTRAINT nudge_preferences_pkey PRIMARY KEY (id);


--
-- Name: personality_profiles personality_profiles_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.personality_profiles
    ADD CONSTRAINT personality_profiles_pkey PRIMARY KEY (id);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- Name: idx_conversations_user_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_conversations_user_id ON public.conversations USING btree (user_id);


--
-- Name: idx_goals_user_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_goals_user_id ON public.goals USING btree (user_id);


--
-- Name: idx_journal_entries_user_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_user_id ON public.journal_entries USING btree (user_id);


--
-- Name: idx_memories_user_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_memories_user_id ON public.memories USING btree (user_id);


--
-- Name: idx_messages_conversation_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_messages_conversation_id ON public.messages USING btree (conversation_id);


--
-- Name: idx_mood_summaries_user_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_mood_summaries_user_id ON public.mood_summaries USING btree (user_id);


--
-- Name: idx_nudge_history_user_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_nudge_history_user_id ON public.nudge_history USING btree (user_id);


--
-- Name: idx_nudge_preferences_user_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_nudge_preferences_user_id ON public.nudge_preferences USING btree (user_id);


--
-- Name: idx_personality_profiles_user_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_personality_profiles_user_id ON public.personality_profiles USING btree (user_id);


--
-- Name: conversations conversations_personality_profile_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.conversations
    ADD CONSTRAINT conversations_personality_profile_id_fkey FOREIGN KEY (personality_profile_id) REFERENCES public.personality_profiles(id);


--
-- Name: conversations conversations_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.conversations
    ADD CONSTRAINT conversations_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- Name: goals goals_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.goals
    ADD CONSTRAINT goals_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- Name: journal_entries journal_entries_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.journal_entries
    ADD CONSTRAINT journal_entries_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- Name: memories memories_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.memories
    ADD CONSTRAINT memories_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- Name: messages messages_conversation_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_conversation_id_fkey FOREIGN KEY (conversation_id) REFERENCES public.conversations(id);


--
-- Name: mood_summaries mood_summaries_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.mood_summaries
    ADD CONSTRAINT mood_summaries_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- Name: nudge_history nudge_history_nudge_preference_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.nudge_history
    ADD CONSTRAINT nudge_history_nudge_preference_id_fkey FOREIGN KEY (nudge_preference_id) REFERENCES public.nudge_preferences(id);


--
-- Name: nudge_history nudge_history_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.nudge_history
    ADD CONSTRAINT nudge_history_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- Name: nudge_preferences nudge_preferences_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.nudge_preferences
    ADD CONSTRAINT nudge_preferences_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- Name: personality_profiles personality_profiles_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.personality_profiles
    ADD CONSTRAINT personality_profiles_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- PostgreSQL database dump complete
--

